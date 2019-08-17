
#ifndef CALCULATOR_UTILS_H
#define CALCULATOR_UTILS_H

/////////////////////////////////////////////环境
//#define ENV_TEST
#define ENV_PROD




/////////////////////////////////////////////针对环境的快捷设置

#ifdef ENV_DEV
#define LOG_LEVEL_VERBOSE
#endif //ENV_DEV

#ifdef ENV_TEST
#define LOG_LEVEL_VERBOSE
#endif //ENV_TEST

#ifdef ENV_PROD
#define LOG_LEVEL_WARNING
#endif //ENV_PROD




/////////////////////////////////////////////log
#ifdef LOG_LEVEL_VERBOSE

#include "iostream"

using namespace std;
#define logv(s) cout<<"[VERBOSE]:"<<s;
#define logd(s) cout<<s;
//#define logd(s) cout<<"[DEBUG  ]:"<<s;
#define logi(s) cout<<"[INFO   ]:"<<s;
#define logw(s) cout<<"[WARNING]:"<<s;
#define loge(s) cout<<"[ERROR  ]:"<<s;
#endif //LOG_LEVEL_VERBOSE


#ifdef LOG_LEVEL_DEBUG
#define logv(s) cout<<"[VERBOSE]:"<<s;
#define logd(s) cout<<"[DEBUG  ]:"<<s;
#define logi(s) cout<<"[INFO   ]:"<<s;
#define logw(s) cout<<"[WARNING]:"<<s;
#define loge(s) cout<<"[ERROR  ]:"<<s;
#endif //LOG_LEVEL_DEBUG


#ifdef LOG_LEVEL_INFO
#define logv(s) cout<<"[VERBOSE]:"<<s;
#define logd(s) cout<<"[DEBUG  ]:"<<s;
#define logi(s) cout<<"[INFO   ]:"<<s;
#define logw(s) cout<<"[WARNING]:"<<s;
#define loge(s) cout<<"[ERROR  ]:"<<s;
#endif //LOG_LEVEL_INFO


#ifdef LOG_LEVEL_WARNING
#define logv(s);
#define logd(s);
#define logi(s);
#define logw(s) cout<<"[WARNING]:"<<s;
#define loge(s) cout<<"[ERROR  ]:"<<s;
#endif //LOG_LEVEL_WARNING


#ifdef LOG_LEVEL_ERROR
#define logv(s) cout<<"[VERBOSE]:"<<s;
#define logd(s) cout<<"[DEBUG  ]:"<<s;
#define logi(s) cout<<"[INFO   ]:"<<s;
#define logw(s) cout<<"[WARNING]:"<<s;
#define loge(s) cout<<"[ERROR  ]:"<<s;
#endif //LOG_LEVEL_ERROR


#endif //CALCULATOR_UTILS_H