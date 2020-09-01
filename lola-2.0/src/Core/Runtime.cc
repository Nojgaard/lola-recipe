/****************************************************************************
  This file is part of LoLA.

  LoLA is free software: you can redistribute it and/or modify it under the
  terms of the GNU Affero General Public License as published by the Free
  Software Foundation, either version 3 of the License, or (at your option)
  any later version.

  LoLA is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
  more details.

  You should have received a copy of the GNU Affero General Public License
  along with LoLA. If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/

/*!
\file
\author Niels
\status new

\brief Implementation of runtime specific functionality.
*/

#include <Core/Handlers.h>
#include <Core/Runtime.h>
#include <InputOutput/InputOutput.h>
#include <InputOutput/Socket.h>

#include <libgen.h>
#include <unistd.h>
#include <new>
#include <cstdlib>
#include <csignal>

/*!
A JSON data store to collect all kinds of structured information in a key/value
fashion. The result can be printed with the `--json' parameter and is sent to
a logging server with the callHome() function.
*/
JSON RT::data;

/*!
A thread to implement the time limit provided by the `--timelimit' parameter.
*/
pthread_t RT::reporter_thread;

/*!
This reporter will be initialized by evaluateParameters() and used throughout
the execution of LoLA. Furthermore, it is set by IO::setReporter to be used to
report opening and closing of files.

\ingroup g_reporting
*/
Reporter *RT::rep;

/*!
\note variable is initialized by function evaluateParameters()
*/
gengetopt_args_info RT::args;

/*!
\note This file is also used in the error function in case of parse errors
*/
Input *RT::currentInputFile = NULL;

/*!
\param argc  the number of command line parameters
\param argv  the array of command line parameters
\brief evaluate the command line parameters
\post variable args is usable
*/
void RT::evaluateParameters(int argc, char **argv)
{
    // strip path information from the tool name to have nicer error messages
    argv[0] = basename(argv[0]);

    // initialize the parameters structure
    struct cmdline_parser_params *params = cmdline_parser_params_create();

    // call the cmdline parser
    if (UNLIKELY(cmdline_parser(argc, argv, &args) != 0))
    {
        RT::rep = new ReporterStream(true);
        IO::setReporter(rep);
        RT::rep->message("invalid command-line parameter(s)");
        RT::rep->abort(ERROR_COMMANDLINE);
    }

    // select a report according to the --reporter option
    switch (args.reporter_arg)
    {
    case reporter_arg_stream:
        rep = new ReporterStream(!args.quiet_given);
        break;

    case reporter_arg_socket:
        rep = new ReporterSocket((u_short)args.outputport_arg,
                                 args.address_arg, !args.quiet_given);
        rep->message("pid = %d", getpid());
        break;

    case reporter_arg_silent:
        rep = new ReporterSilent();
        break;

    default:
        assert(false);
    }

    // register the reporter to used it for file status messages
    IO::setReporter(rep);

    // further command line parameter checks
    /*
    if (UNLIKELY(args.formula_given and (args.check_arg == check_arg_deadlock or args.check_arg == check_arg_full)))
    {
        rep->status("parameter %s must only be used with %s",
                    RT::rep->markup(MARKUP_PARAMETER, "--formula").str(),
                    RT::rep->markup(MARKUP_PARAMETER, "--check=modelchecking").str());
        rep->abort(ERROR_COMMANDLINE);
    }
    */

    free(params);
}


/*!
\note can be switched off with the command line option `--nolog`
*/
void RT::callHome()
{
    // call home unless option --nolog is used
    if (not RT::args.nolog_given)
    {
        Socket et(5000, "stats.service-technology.org", false);
        et.send(data.toString().c_str());
    }
}

/*!
\param argc  the number of command line parameters (got from main())
\param argv  the array of command line parameters (got from main())
*/
void RT::initialize(int argc, char **argv)
{
    // install exit handler for ordered exit()
    Handlers::installExitHandler();

    // initialize JSON data
    data["call"]["package_version"] = PACKAGE_VERSION;
    data["call"]["svn_version"] = VERSION_SVN;
    data["call"]["build_system"] = CONFIG_BUILDSYSTEM;
    data["call"]["hostname"] = CONFIG_HOSTNAME;
    data["call"]["architecture"] = SIZEOF_VOIDP * 8;
#ifdef NDEBUG
    data["call"]["assertions"] = false;
#else
    data["call"]["assertions"] = true;
#endif
#ifdef USE_PERFORMANCE
    data["call"]["optimizations"] = true;
#else
    data["call"]["optimizations"] = false;
#endif
    for (int i = 1; i < argc; ++i)
    {
        data["call"]["parameters"] += argv[i];
    }

    // parse the command line parameters
    evaluateParameters(argc, argv);

    // process call data
    callHome();

    // install termination handler for ordered premature termination
    Handlers::installTerminationHandlers();

    // install new handler
    std::set_new_handler(Handlers::newHandler);

    if (args.timelimit_given)
    {
        rep->status("LoLA will run for %d seconds at most (%s)",
                    args.timelimit_arg, RT::rep->markup(MARKUP_PARAMETER, "--timelimit").str());
        const int ret = pthread_create(&reporter_thread, NULL, reporter_internal, NULL);
        // LCOV_EXCL_START
        if (UNLIKELY(ret != 0))
        {
            rep->status("thread could not be created");
            rep->abort(ERROR_THREADING);
        }
        // LCOV_EXCL_STOP
    }
}

/*!
Implements a global time limit for LoLA. This function is called in a thread
that waits the given amount of time and then terminates LoLA with the SIGUSR1
signal.
*/
void *RT::reporter_internal(void *)
{
    sleep(args.timelimit_arg);
    RT::rep->status(RT::rep->markup(MARKUP_IMPORTANT, "time limit reached - aborting").str());

    // abort LoLA by sending SIGUSR1 signal
    kill(getpid(), SIGUSR1);

    return NULL;
}
