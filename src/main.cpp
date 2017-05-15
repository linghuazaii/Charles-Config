#include "charles_config.h"

int main(int argc, char **argv) {
    CharlesConfig conf;
    conf.loadConfig("../conf/test.conf");
    
    return 0;
}
