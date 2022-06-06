#include <netdb.h>
#include <arpa/inet.h>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <string>
#include <curl/curl.h>
#include <curl/easy.h>
#include <openssl/crypto.h>

using namespace std;

void show_usage(std::string name)
{
    std::cerr << "\nUsage: " << name << " <options> \n"
              << "Options:\n"
              << "\t-h,--help\n\t\tShow this help message\n"
              << "\t-d,--dns Use internal DNS Server Setting yes/no\n\t\t Use internal DNS server setting or not\n"
              << "\t-u,--url URL\n\t\tSpecify the url to connect\n"
              << "Example:\n"
              << "\t" << name << "--dns yes --url www.google.com\n"
              << std::endl;
}

int main( int argc, char** argv )
{ 
    string dns_server_set, url;
    string google_dns_ips="8.8.8.8, 8.8.4.4";

    if (argc < 4) 
    {
        show_usage(argv[0]);
        return 1;
    }
    for (int i = 1; i < argc; ++i) 
    {
        std::string arg = argv[i];
        if ((arg == "-h") || (arg == "--help")) 
        {
            show_usage(argv[0]);
            return 0;
        } 
        else if ((arg == "-d") || (arg == "--dns")) 
        {
            if (i + 1 < argc) // Make sure we aren't at the end of argv!
            { 
                dns_server_set = argv[++i]; // Increment 'i' so we don't get the argument as the next argv[i].
                cout << endl << "Custom DNS Server: " << dns_server_set << endl;
            } 
            else 
            { // Uh-oh, there was no argument to the option.
                  std::cerr << "--dns option requires one argument." << std::endl;
                return 1;
            }  
        } 
        else if ((arg == "-u") || (arg == "--url")) 
        {
            if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                url = argv[++i]; // Increment 'i' so we don't get the argument as the next argv[i].
                cout << endl << "URL: " << url.c_str() << endl;
            } 
            else { // Uh-oh, there was no argument to the option.
                  std::cerr << "--url option requires one argument." << std::endl;
                return 1;
            }  
        } 
    }

    curl_global_init( CURL_GLOBAL_ALL );
    CURL *curl = curl_easy_init();

    if(curl) {
        // ask libcurl to show us the verbose output *
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        if(dns_server_set == "yes") 
        {
            cout << "This requires libcurl built with name resolving backend that needs using c-ares." << endl;
            cout << "Will use " << google_dns_ips << " as DNS" << endl;
            curl_easy_setopt(curl, CURLOPT_DNS_SERVERS, google_dns_ips.c_str()); //  google dns
        }
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    
        // curl_easy_setopt(curl, CURLOPT_URL, "35.247.112.170:80/v1/request/");

        // curl_easy_setopt(curl, CURLOPT_URL, "www.amazon.com/");
        // curl_easy_setopt(curl, CURLOPT_URL, "108.138.6.128/");

        // curl_easy_setopt(curl, CURLOPT_URL, "www.google.com/");
        // curl_easy_setopt(curl, CURLOPT_URL, "172.217.20.68/");
        
        auto res = curl_easy_perform(curl);
        cout << res << endl; 
        curl_easy_cleanup(curl);
    }  
    exit(0);
}
