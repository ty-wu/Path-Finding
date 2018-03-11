//
//  main.cpp
//  zoo
//
//  Created by tianyuan wu on 2017/6/12.
//  Copyright © 2017年 tianyuan wu. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <getopt.h>
#include <sstream>
#include "controller.h"

//printHelp
void printHelp(char* argv[]) {
    
}
// getMode
// MODIFY: runing mode, output mode
// EFFECT: get input and output mode from the command line
void getMode(int argc, char * argv[], std::string &mode) {
    int getMode = false;
    
    opterr = true;
    int choice;
    int option_index = 0;
    option long_options[] = {
        { "mode", required_argument, nullptr, 'm' },
        { "help", no_argument, nullptr, 'h' },
        { nullptr, 0,  nullptr, '\0' }
    };
    
    while ((choice = getopt_long(argc, argv, "m:h", long_options, &option_index)) != -1) {
        switch(choice) {
            case 'h':
                printHelp(argv);
                exit(0);
                
            case 'm':
                getMode = true;
                mode = optarg;
                if (mode == "MST" || mode == "OPTTSP" || mode == "FASTTSP") {
                    break;
                }
                else {
                    std::cerr << "Error: Invalid Mode Type" << std::endl;
                    exit(1);
                }
                
                
            default:
                std::cerr << "Error: invalid option " << std::endl;
                exit(1);
        }
    }
    
    if (getMode == false) {
        std::cerr << "Error: Mode Option Required" << std::endl;
        exit(1);
    }
    
    
} // getMode()


int main(int argc, char * argv[]) {
#ifdef __APPLE__
    freopen("/Users/tianyuanwu/Desktop/samples (2)/sample-c.txt", "r", stdin);
#endif
    std::ios::sync_with_stdio(false);
    std::cout << std::setprecision(2);
    std::cout << std::fixed;
    
    std::string mode;
    getMode(argc, argv, mode);
    
    if (mode == "MST") {
        std::ostringstream os;
        MST ctl;
        ctl.initeForMST();
        ctl.genMST(os);
    }
    
    else if (mode == "FASTTSP") {
        std::ostringstream os;
        FASTTSP ctl;
        ctl.genFTSP(os);

        
    }
    
    else {
        OPTTSP ctl;
        ctl.genOPTTSP();
    }
    
    return 0;
}
