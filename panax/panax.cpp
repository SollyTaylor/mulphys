
#include <stdio.h>
#include <iostream>
#include <string>
#include <QHash>
#include <QDebug>
#include <vector>

#include "tclap/CmdLine.h"
#include "SysQt.h"
#include "SysQtEx.h"
#include "tsp_runner.h"

//#include <QApplication>

const unsigned int tsp_version_major = 0;
const unsigned int tsp_version_minor = 9;
const unsigned int tsp_version_patch = 8;

int main(int argc, char* argv[]){

//    QApplication a(argc, argv);

    const std::string& pid = QString::number(QCoreApplication::applicationPid()).toStdString();
    tsp::Sys::info("The tsp Process ID: " + pid);

    std::string version_value = tsp::get_version(tsp_version_major, tsp_version_minor, tsp_version_patch);
    TCLAP::CmdLine cmd("tsp command line tool.", 'v', version_value);

    TCLAP::SwitchArg is_all_opt(
                "a", // abbrev -a
                "all", // full, --all
                "apply to all modules in scenario"
                );
    cmd.add(is_all_opt);

    TCLAP::SwitchArg is_debug_opt(
                "d", // abbrev -d
                "debug", // full, --debug
                "indicate debug version of module"
                );
    cmd.add(is_debug_opt);

    TCLAP::SwitchArg is_force_opt(
                "f", // abbrev -f
                "force", // full, --force
                "forcely register"
                );
    cmd.add(is_force_opt);

    TCLAP::SwitchArg is_output_opt(
                "o", // abbrev -o
                "output", // full, --output
                "write out tecplot file to check"
                );
    cmd.add(is_output_opt);

    TCLAP::SwitchArg is_local_opt(
                "l", // abbrev -l
                "local", // full, --local
                "local install flag"
                );
    cmd.add(is_local_opt);

    TCLAP::MultiArg<std::string> port_options(
                "p", // abbrev -p, -pv"xxxxxxxx"
                "port", // full, --port
                "port options",
                false,
                "string"
                );
    cmd.add(port_options);

    TCLAP::MultiArg<std::string> role_options(
                "c", // abbrev -c, -cv"xxxxxxxx"
                "connectorrole", // full, --connectorrole
                "connector role options only for connector test running",
                false,
                "string"
                );
    cmd.add(role_options);

    TCLAP::MultiArg<std::string> time_options(
                "t", // abbrev -t, -tv"dt:0.02/tmax:12.0"
                "time", // full, --time
                "time options for specifying dt and tmax",
                false,
                "string"
                );
    cmd.add(time_options);


    TCLAP::UnlabeledMultiArg<std::string> operation_opts(
                "operation_series",
                "operation type + module_name, [create/test/register/install/uninstall] + module_name",
                false,
                "operation + module_name"
                );
    cmd.add(operation_opts);

    // parse
    cmd.parse(argc, argv);

    // get the option
    std::vector<std::string>  op_opts = operation_opts.getValue();
    std::vector<std::string>  pt_opts = port_options.getValue();
    std::vector<std::string>  role_opts = role_options.getValue();
    std::vector<std::string>  tm_opts = time_options.getValue();

    bool is_local_install = is_local_opt.getValue();
    bool is_force_register = is_force_opt.getValue();
    bool is_debug_option = is_debug_opt.getValue();
    bool is_all_option = is_all_opt.getValue();
    bool is_output_option = is_output_opt.getValue();
    size_t n_opts = op_opts.size();
    try
    {
        {
            std::stringstream ss;
            ss << "Update tsp environment variables";
            tsp::Sys::info(ss.str());
            tsp::update_tsp_env_var();
        }

        if (op_opts.size())
        {
        switch(tsp::convert_action_option(op_opts[0]))
        {
        case tsp::ACT_CREATE:
        {
            std::stringstream ss;
            if(n_opts!=2)
            {
                ss << "Command line tsp create takes 2 arguments." << std::endl;
                ss << "test command initialize one module project each time." << std::endl;
                ss << "e.g. cli:  " << std::endl;
                ss << "tsp create tsp_solver_some_module_name" << std::endl;
                tsp::tspinfo(ss);
                return -1;
            }
            // get number of module names
            tsp::tsp_act_create(tsp::StdStr2QStr(op_opts[1]));
            break;
        }
        case tsp::ACT_TOUCH:
        {
            std::stringstream ss;
            if(n_opts!=2)
            {
                ss << "Command line tsp create takes 2 arguments." << std::endl;
                ss << "test command create a new module case instance." << std::endl;
                ss << "e.g. cli:  " << std::endl;
                ss << "tsp touch model_name" << std::endl;
                tsp::tspinfo(ss);
                return -1;
            }
            tsp::tsp_act_touch( tsp::StdStr2QStr(op_opts[1]) );
            break;
        }

        case tsp::ACT_NEW_ID:
        {
            if(n_opts!=1)
            {
                std::stringstream ss;
                ss << "Command line tsp newid takes 1 arguments." << std::endl;
                ss << "generate a new resource id." << std::endl;
                ss << "e.g. cli:  " << std::endl;
                ss << "tsp newid" << std::endl;
                tsp::tspinfo(ss);
                return -1;
            }
//            {
//                const std::string rand_id = tsp::generate_random_id(23);
//                tsp::Sys::info("Random 23-bit id: \n\t" + rand_id + "\n");
//            }
            {
//                const std::string uuid_v0 = tsp::generate_uuid_v0();
                const std::string uuid_v1 = tsp::generate_uuid_v1();
//                const std::string uuid_v4 = tsp::generate_uuid_v4();
//                tsp::Sys::info("UUID version 0: \n\t" + uuid_v0 + + "\n");
                tsp::Sys::info("UUID version 1: \n\t" + uuid_v1 + + "\n");
//                tsp::Sys::info("UUID version 4: \n\t" + uuid_v4 + + "\n");
            }
            break;
        }

        case tsp::ACT_HASH:
        {
            std::stringstream ss, ss1;
            if(n_opts!=2)
            {
                ss << "Command line tsp hash takes 1 arguments." << std::endl;
                ss << "generate a new hash number of any string." << std::endl;
                ss << "e.g. cli:  " << std::endl;
                ss << "tsp hash <some_string>" << std::endl;
                tsp::tspinfo(ss);
                return -1;
            }
            unsigned int hash_number = tsp::Sys::ELFHash(op_opts[1]);
            ss1 << "Newly generated hash number of std::string: "
                << op_opts[1] << std::endl
                << " is " << hash_number;
            tsp::Sys::info(ss1.str());
            break;
        }
        case tsp::ACT_READ:
        {
            double sf = 1.0;
            if(n_opts!=4 && n_opts!=3)
            {
                std::stringstream ss;
                ss << "Command line tsp read takes 3/4 arguments." << std::endl;
                ss << "e.g. cli:  " << std::endl;
                ss << "(takes 3)$tsp read tsp_reader_stl_ascii radar.stl" << std::endl;
                ss << "(takes 4)$tsp read tsp_reader_stl_ascii radar.stl 1.0" << std::endl;
                tsp::tspinfo(ss);
                return -1;
            }
            else if (n_opts == 4)
            {
                bool OK = false;
                sf = tsp::StdStr2QStr(op_opts[3]).toDouble(&OK);
                if (!OK)
                {
                    std::stringstream ss;
                    ss << "Failed to convert scale factor: " << op_opts[3] << std::endl;
                    tsp::tspinfo(ss);
                    return -1;
                }
            }
            const QString module_name = tsp::StdStr2QStr(op_opts[1]);
            const QString geom_file = tsp::StdStr2QStr(op_opts[2]);
            tsp::tsp_act_read(module_name, geom_file, sf, is_debug_option);
            break;
        }
        case tsp::ACT_READSOL:
        {
            if(n_opts!=3)
            {
                std::stringstream ss;
                ss << "Command line tsp readsol takes 3 arguments." << std::endl;
                ss << "e.g. cli:  " << std::endl;
                ss << "(takes 3)$tsp readsol tsp_reader_stl_ascii radar.stl" << std::endl;
                tsp::tspinfo(ss);
                return -1;
            }
            else
            {
                const QString module_name = tsp::StdStr2QStr(op_opts[1]);
                const QString geom_file = tsp::StdStr2QStr(op_opts[2]);
                tsp::tsp_act_readsol(module_name, geom_file, 1.0, is_debug_option);
            }
            break;
        }
        case tsp::ACT_PACK:
        {
            if (n_opts != 1)
            {
                std::stringstream ss;
                ss << "Command line tsp pack takes 1 argument." << std::endl;
                ss << "e.g. cli:  " << std::endl;
                ss << "(takes 1)$tsp pack (tspd pack -d)" << std::endl;
                tsp::tspinfo(ss);
                return -1;
            }
            else
            {
                tsp::tsp_act_pack();
            }
            break;
        }
        case tsp::ACT_UNPACK:
        {
            if (n_opts != 1)
            {
                std::stringstream ss;
                ss << "Command line tsp unpack takes 1 argument." << std::endl;
                ss << "e.g. cli:  " << std::endl;
                ss << "(takes 1)$tsp unpack (tspd unpack -d)" << std::endl;
                tsp::tspinfo(ss);
                return -1;
            }
            else
            {
                tsp::tsp_act_unpack();
            }
            break;
        }
        case tsp::ACT_EXTRACT:
        {
            if (n_opts != 1)
            {
                std::stringstream ss;
                ss << "Command line tsp extract takes 1 argument." << std::endl;
                ss << "e.g. cli:  " << std::endl;
                ss << "(takes 1)$tsp extract (tspd extract -d)" << std::endl;
                tsp::tspinfo(ss);
                return -1;
            }
            else
            {
                tsp::tsp_act_extract();
            }
            break;
        }
        case tsp::ACT_RECOVER:
        {
            if (n_opts != 1)
            {
                std::stringstream ss;
                ss << "Command line tsp recover takes 1 argument." << std::endl;
                ss << "e.g. cli:  " << std::endl;
                ss << "(takes 1)$tsp recover (tspd recover -d)" << std::endl;
                tsp::tspinfo(ss);
                return -1;
            }
            else
            {
                tsp::tsp_act_recover();
            }
            break;
        }
        case tsp::ACT_TEST:
        {
            // test the resource in current folder
            //
            /*
             *
             *
             ** search for the module name and run
             ** serveral places to search:
             ** (1) local tsp_module folder
             ** (2) system installation folder $TSP_INSTALLATION/resources
             ** (3) module warehouse of www.mbsecloud.com
             *
             * tsp(d) test -a (-d)
             *
             */
            if(n_opts !=2 && n_opts != 1)
            {
                std::stringstream ss;
                ss << "Command line tsp test takes 1 or 2 arguments." << std::endl;
                ss << "e.g. cli:  " << std::endl;
                ss << "(takes 2)$tsp test tsp_solver_super_neighbors -d" << std::endl;
                ss << "(takes 2)$tsp test tsp_environment_USSA1976" << std::endl;
                ss << "(takes 1)$tsp test " << std::endl;
                tsp::tspinfo(ss);
                return -1;
            }
            else if (n_opts == 2)
            {
                const QString module_name = tsp::StdStr2QStr(op_opts[1]);
                // const QString geom_file("");
                tsp::tsp_act_test(module_name,
                                  is_output_option,
                                  is_debug_option);
            }
            else // to test all resources
            {
                // test all resources
                // (1)
                QStringList dirs;
                QString cwd = QDir::currentPath();
                QDir cwddir = QDir::current();
                dirs = cwddir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::NoSymLinks);
                std::stringstream ss;
                ss << dirs.size() << " directories would be processed.";
                tsp::tspinfo(ss);

                for(size_t id = 0; id<dirs.size(); id++)
                {
                    QFileInfo qfi(dirs[id]);
                    QString dir_name = qfi.fileName();

                    // (2)
                    std::string module_type_name;
                    bool verbosity = false;
                    bool good_module = tsp::check_module_name_rule(dir_name.toStdString(),
                                                                   module_type_name,
                                                                   verbosity);
                    if (good_module)
                    {
                        QString path = cwd + "/" + dirs[id];
                        QString module_name = dir_name;

                        QDir::setCurrent(path);
                        if (!tsp::file_exists(path + "/test_exemption_for_registration"))
                        {
                            tsp::RSC_OPT rsc_opt = tsp::get_resource_type(module_type_name);
                            if (rsc_opt == tsp::RSC_ENVIRONMENT
                                     ||
                                     rsc_opt == tsp::RSC_MATERIAL
                                     ||
                                     rsc_opt == tsp::RSC_PROVIDER
                                     ||
                                     rsc_opt == tsp::RSC_READER
                                     ||
                                     rsc_opt == tsp::RSC_SOLVER
                                    )
                            {
                                // (5) make the test of target version
                                tsp::tsp_act_test(module_name,
                                                  is_output_option,
                                                  is_debug_option);
                            }
                        }
                        else
                        {
                            std::stringstream ss;
                            ss << "The test after registration for module "
                               << module_name.toStdString()
                               << " has been exempted for the existence of file"
                               << _QUOTE(dir_name.toStdString());
                            tsp::Sys::info(ss.str());
                        }
                    } // end of good modules
                    else
                    {
                        const std::string dir_str = dir_name.toStdString();
                        std::stringstream ss;
                        ss << "The directory "
                           << _QUOTE(dir_str)
                           << " is not a module, directory parsing continued.";
                        tsp::Sys::info(ss.str());
                    }
                } // end loop on all dirs
            }
            break;
        }

        case tsp::ACT_REGISTER:
        {
            QString module_to_register("");

            if(n_opts!=1 && n_opts != 2)
            {
                std::stringstream ss;
                ss << "tsp register requires zero or one parameter to proceed. " << std::endl;
                ss << "e.g. cli:  " << std::endl;
                ss << "$ tsp register -f -a" << std::endl;
                tsp::tspinfo(ss);
                return -1;
            }
            else
            {

                if (n_opts == 2)
                {
                    module_to_register = tsp::StdStr2QStr(op_opts[1]);
                }

                // (1) get all directories in current dir
                // (2) get all directories names and check whether meets the module_name rule
                // (3) cd inside the dirs
                // (4) tsp_act_register
                // (5) loop back (1)

                // (1)
                QStringList dirs;
                QString cwd = QDir::currentPath();
                if(is_all_option) // if register all
                {
                    QString build_type("Debug");
#if  defined( QT_DEBUG )
                    build_type = "Debug";
#else
                    build_type = "Release";
#endif
//                    QDir cwd = QDir::current();
                    QString platform(tsp::get_platform().c_str());
#if defined(Q_OS_WIN64)
                    cwd = QDir::currentPath() + "/lib_x64/" + platform + "/" + build_type;
#elif defined(Q_OS_WIN32) && !defined(Q_OS_WIN64)
                    cwd = QDir::currentPath() + "/lib_x86/" + platform + "/" + build_type;
#endif
                    QDir cwd_lib = QDir(cwd);

                    dirs = cwd_lib.entryList(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::NoSymLinks);
                    std::stringstream ss;
                    ss << dirs.size() << " directories would be processed.";
                    tsp::tspinfo(ss);

                    // clear all data in "db" and "id-name" in modules.json file
                    tsp::clear_modules_json_db();
                }
                else // (2) if register current
                {
                    dirs << cwd;
                }

                auto check_module_name = []
                        (const QString& module_name,
                        std::string& module_type_name)
                {
                    bool verbosity = false;
                    bool good_module = tsp::check_module_name_rule(module_name.toStdString(),
                                                                   module_type_name,
                                                                   verbosity);
//                    tsp::Sys::info("Registering a " + module_type_name);
                    return good_module;
                };

                typedef std::multimap<int, std::string> NewDirs;
                auto sort_register_sequence = [&dirs, check_module_name]()
                {
                    typedef std::map<std::string, int> ModuleTypeOrder;
                    static ModuleTypeOrder mto;
                    int order = 0;
                    {
                        // peripherals
                        mto["material"] = order++;
                        mto["provider"] = order++;
                        mto["environment"] = order++;
                        mto["connector"] = order++;
                        mto["reader"] = order++;
                        mto["integrator"] = order++;
                        mto["interpolator"] = order++;

                        mto["batch"] = order++;
                        mto["controller"] = order++;
                        mto["writer"] = order++;
                        mto["recorder"] = order++;
                        // model and related modules
                        mto["solver"] = order++;
                        mto["dynamics"] = order++;
                        mto["model"] = order++;
                        mto["evaluator"] = order++;
                        mto["analyzer"] = order++;

                        // the rest of orders
                        int preserved = -1;
                        mto["geometry"] = preserved;
                        mto["simulation"] = preserved;
                        mto["expectation"] = preserved;
                        mto["mission"] = preserved;
                        mto["prescript"] = preserved;
                        mto["solreader"] = preserved;

                    }
                    auto assert_in_mto = [](const std::string& type_name, const ModuleTypeOrder& mto)
                    {
                        if (mto.find(type_name) != mto.end() && mto.at(type_name) != -1)
                            return true;
                        else
                        {
                            std::stringstream ss;
                            ss << "The module type name "
                               << _QUOTE(type_name)
                               << " is not ready for registration.";
                            THROW_TSPEXCEPTION_INFO(ss.str());
                            return false;
                        }
                    };

                    NewDirs module_order;
                    for (size_t it = 0; it<dirs.size(); ++it)
                    {
                        QFileInfo qfi(dirs[it]);
                        QString module_name = qfi.fileName();
                        std::string module_type_name;
                        if (
                                check_module_name(module_name, module_type_name)
                                &&
                                assert_in_mto(module_type_name, mto)
                                )
                        {
                            module_order.insert(std::make_pair(mto[module_type_name], module_name.toStdString()));
//                            module_order[] = module_name;
                        }
                    }
                    QStringList newdirs;
                    for (NewDirs::const_iterator it = module_order.begin();
                         it != module_order.end();
                         ++it)
                    {
                        QString dir(it->second.c_str());
                        newdirs.push_back(dir);
                    }
                    dirs = newdirs;
                    return;
                };

                auto register_all =
                        [
                        &dirs,
                        &cwd,
                        is_force_register,
                        is_debug_option,
                        check_module_name,
                        &module_to_register
                        ]()
                {
                    for(size_t id = 0; id<dirs.size(); id++)
                    {
                        QFileInfo qfi(dirs[id]);
                        QString module_name = qfi.fileName();
                        if (module_to_register != "" && module_name != module_to_register)
                        {
//                            tsp::get_module_file_path(module_to_register, tsp::is_debug_build_type());
                            continue;
                        }
                        // (2)
                        std::string dummy_module_type;
                        bool good_module = check_module_name(module_name, dummy_module_type);
                        if (good_module)
                        {
                            QString path = cwd + "/" + dirs[id];

                            QDir::setCurrent(path);
                            // (3)
                            std::stringstream ss;
                            ss << "-------------------------------------------" << std::endl;
                            ss << "Entering path: " << path.toStdString() << std::endl;
                            ss << "cwd: " << QDir::currentPath().toStdString();
                            tsp::tspinfo(ss);

                            // (4) register plugins debug/release version
                            if(is_debug_option) // only debug -d
                            {
                                tsp::tsp_act_register(is_force_register, is_debug_option);
                            }
                            // no options means register both release versions
                            else
                            {
                                // register the release version
                                tsp::tsp_act_register(is_force_register);
                            }

                            // register json files
                            tsp::tsp_act_register_json(module_name, is_debug_option);

                        } // good module
                        else
                        {
                            const std::string dir_str = module_name.toStdString();
                            std::stringstream ss;
                            ss << "The directory "
                               << _QUOTE(dir_str)
                               << " is not a module, directory parsing continued.";
                            tsp::Sys::info(ss.str());
                            continue;
                        }
                        // (5)
                    }
                };

                sort_register_sequence();
                register_all();

            }
            break;
        }
        case tsp::ACT_UPLOAD:
        {
            if(n_opts!=1 && n_opts!=2 && n_opts !=3)
            {
                std::stringstream ss;
                ss << "tsp upload requires no other parameters. " << std::endl;
                ss << "e.g. cli:  " << std::endl;
                ss << "$ tsp upload" << std::endl;
                ss << "$ tsp upload http://129.134.87.90" << std::endl;
                ss << "$ tsp upload test.tspgeom http://129.134.87.90" << std::endl;
                tsp::tspinfo(ss);
                return -1;
            }
            else if(n_opts == 1)
            {
                tsp::tsp_act_upload("");
            }
            else if(n_opts == 2)
            {
                QString target = QString::fromStdString(op_opts[1]);
                bool isGeom = target.endsWith(QString("tspgeom"));
                if (isGeom)
                {
                    tsp::tsp_act_upload_geometry(target.toStdString());
                }
                else
                {
                    tsp::tsp_act_upload(op_opts[1]);
                }
            }
            else // n_opts == 3
            {
                QString target = QString::fromStdString(op_opts[1]);
                bool isGeom = target.endsWith(QString("tspgeom"));
                tsp::tsp_act_upload_geometry(target.toStdString(), op_opts[2]);
            }
            break;
        }
        case tsp::ACT_UNREGISTER:
        {
            if(n_opts!=2)
            {
                std::stringstream ss;
                ss << "tsp unregister requires module name. " << std::endl;
                ss << "e.g. cli:  " << std::endl;
                ss << "$ tsp unregister tsp_solver_pem" << std::endl;
                tsp::tspinfo(ss);
                return -1;
            }
            else
            {
                const QString module_name = tsp::StdStr2QStr(op_opts[1]);
                //no matter the build type is, the command would unregister
                // both build versions
//                if(is_debug_option && !is_release_option) // only debug -d
//                {
//                    tsp::tsp_act_unregister(module_name, is_debug_option);
//                }
//                else if (!is_debug_option && is_release_option) // only release -r
//                {
//                    tsp::tsp_act_unregister(module_name);
//                }
//                // no options means register both debug/release versions
//                else if (!is_debug_option && !is_release_option)
                {
                    tsp::tsp_act_unregister(module_name);
                    tsp::tsp_act_unregister(module_name, true);
                }
//                else
//                {
//                    std::stringstream ss;
//                    ss << "tsp unregister options -d/-r both set is illeagal" << std::endl;
//                    ss << "possible cli's:  " << std::endl;
//                    ss << "(unregister debug/release)$ tsp unregister" << std::endl;
//                    ss << "(unregister release)$ tsp unregister -r" << std::endl;
//                    ss << "(unregister debug)$ tsp unregister -d" << std::endl;
//                    tsp::tspinfo(ss);
//                    return -1;
//                }
            }
            break;
        }
        case tsp::ACT_INSTALL:
        {
            if(n_opts<2)
            {
                std::stringstream ss;
                ss << "Too few command line input, use tsp --help for help" << std::endl;
                ss << "e.g. cli:  " << std::endl;
                ss << "(for globally install: ) $ tsp install tsp_solver_kkk tsp_reader_dtf" << std::endl;
                ss << "(for locally install:  ) $ tsp install tsp_solver_kkk tsp_reader_dtf -l" << std::endl;
                tsp::tspinfo(ss);
                return -1;
            }
            else
            {
                // get number of module names
                for(size_t i_opt = 1; i_opt<n_opts; i_opt++)
                {
                    if(is_local_install)
                    {
                        tsp::tsp_act_install(tsp::StdStr2QStr(op_opts[i_opt]),  true);
                    }
                    else
                    {
                        tsp::tsp_act_install(tsp::StdStr2QStr(op_opts[i_opt]));
                    }
                }
            }
            break;
        }

        case tsp::ACT_RUN:
        {
            if (n_opts>=2)
            {
                const std::string& target = op_opts[1];

                //
                // possible targets:
                //
                // "model"
                // "batch"
                // "controller"
                // "recorder"
                // "connector"
                // "analyzer"
                //
                tsp::RSC_OPT resource_opt = tsp::get_resource_type(target);
                switch(resource_opt)
                {
                case tsp::RSC_MODEL:{
                    tsp_run_model(op_opts, pt_opts, tm_opts);break;}
                case tsp::RSC_RECORDER:{
                    tsp_run_recorder(op_opts, pt_opts);break;}
                case tsp::RSC_CONTROLLER:{
                    tsp_run_controller(op_opts, pt_opts);break;}
                case tsp::RSC_BATCH:{
                    tsp_run_batch(op_opts, pt_opts);break;}
                case tsp::RSC_CONNECTOR:{
                    tsp_run_connector(op_opts, pt_opts, role_opts);break;}
                case tsp::RSC_ANALYZER:{
                    tsp_run_analyzer(op_opts); break;}
                default:
                {
                    std::stringstream ss;
                    ss << "Current target \"" << target << "\" is not runnable.\n";
                    ss << "Possible runnable targets are: \n"
                       << "  - model \n"
                          << "  - batch \n"
                             << "  - controller \n"
                                << "  - recorder \n"
                                    << " - analyzer \n"
                                        << "  - connector \n";
                    ss << "Current engaged target: \"" << target << "\"";
                    THROW_TSPEXCEPTION_INFO(ss.str());
                    break;
                }
                }
            }
            else
            {
                std::stringstream ss;
                ss << "When running tsp(d) run cli error: \n"
                   << " example cli: \n"
                   << " tsp(d) run batch nanomsg -pv<port-string>(-d) ";
                THROW_TSPEXCEPTION_INFO(ss.str());
            }
            break;
        }
        case tsp::ACT_CONF:
        {
            if (n_opts == 1/* && op_opts[1] == "model"*/)
            {
                tsp::Sys::info("Configuring a model...");
                const std::string model_full_name = "tsp_model_gf";
                _PTR<tsp::ModelBase> pmdl = tsp::Model::get(model_full_name);
                pmdl->init(MODEL_DT, MODEL_TMAX);
                pmdl->write_root_dynamics();
            }
            else if (n_opts == 2)
            {
                const std::string& target = op_opts[1];
                tsp::RSC_OPT resource_opt = tsp::get_resource_type(target);
                switch(resource_opt)
                {
                case tsp::RSC_MODEL:
                {
                    // using gf model by default
                    tsp::Sys::info("Configuring a model...");
                    const std::string model_full_name = "tsp_model_gf";
                    _PTR<tsp::ModelBase> pmdl = tsp::Model::get(model_full_name);
                    pmdl->init(MODEL_DT, MODEL_TMAX);
                    pmdl->write_root_dynamics();
                    break;
                }
                case tsp::RSC_SIMULATION:
                {
                    tsp::Sys::info("Configuring a simulation...");
                    tsp::tsp_sim_config(is_debug_option);
                    break;
                }
                default:
                {
                    std::stringstream ss;
                    ss << "The config command only works for model or simulation.";
                    THROW_TSPEXCEPTION_INFO(ss.str());
                    break;
                }
                }
            }
            else
            {
                std::stringstream ss;
                ss << "When running tsp(d) config cli error: \n"
                   << " example cli: \n"
                   << " tsp(d) config model (-d) ";
                THROW_TSPEXCEPTION_INFO(ss.str());
            }
            break;
        }
        case tsp::ACT_JOBID:
        {
            {
                if (op_opts.size() != 2)
                {
                    std::stringstream ss;
                    ss << "When running tsp with jobid, the e.g. cli performed as: \n"
                       << "$ tsp jobid 53e8186d-191b-11e6-986d-94de80faa045";
                    THROW_TSPEXCEPTION_INFO(ss.str());
                }
                std::string jobid = op_opts[1];
                if (!tsp::check_resource_id(jobid))
                {
                    std::stringstream ss;
                    ss << "The jobid explicitly assigned \""
                       << jobid
                       << "\" is not a uuid.";
                    THROW_TSPEXCEPTION_INFO(ss.str());
                }
                tsp::Sys::info("        TSP JOB ID: " + jobid);
                tsp::db& jdb = tsp::db::GetInstance();
                jdb.db_set_jobid(jobid);
            }
            tsp::tsp(is_debug_option);
            break;
        }
        default:
        {
            std::stringstream ss;
            ss << "Operational option is not recognized. Use default running as a simulation.\n";
            ss << "The jobid is not explictly assigned. Use randomly generated uuid.\n";
            std::string jobid = tsp::generate_uuid_v1();
            ss << "        TSP JOB ID: " + jobid;
            tsp::Sys::info(ss.str());
            tsp::db& jdb = tsp::db::GetInstance();
            jdb.db_set_jobid(jobid);
            tsp::tsp(is_debug_option);
            break;
        }
        }
        } // end if operation option size() > 0
        else
        {
            // running simulation
            std::stringstream ss;
            ss << "The jobid is not explictly assigned. Use randomly generated uuid.\n";
            std::string jobid = tsp::generate_uuid_v1();
            ss << "        TSP JOB ID: " + jobid;
            tsp::Sys::info(ss.str());
            tsp::db& jdb = tsp::db::GetInstance();
            jdb.db_set_jobid(jobid);
            tsp::tsp(is_debug_option);
        }
    }
    catch(tsp::tspExceptions& e)
    {
        CATCH_TSPEXCEPTION_INFO;
    }
    catch(std::exception& e)
    {
        CATCH_STDEXCEPTION_INFO;
    }

    std::stringstream ss;
    ss << "TSP Main Program Reached a Normal Termination." << std::endl;
    tsp::Sys::info(ss.str());
    return 0; //a.exec();
}
