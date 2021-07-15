#include <iostream>
#include <regex>
#include "src/stringreader.h"
#include "src/tokenqueue.h"
#include "src/tokenbuilder.h"
#include "src/tokeniterator.h"
#include "src/objectvalue.h"
#include "src/textvalue.h"
#include "src/http/httprequestparser.h"
#include "src/socket/listener.h"
#include "src/http/httpheaderparser.h"
#include "src/http/httpheader.h"
#include "src/objectparser.h"

void testHttpParser() ;
void testHttpParser2() ;
void testHttpHeaderParser();

int main() {
    std::cout << "Hello, World!" << std::endl;
//    StringReader* reader = new StringReader("http[80] : { \n"
//                                            "  domain['www.potalab.com'] : {\n"
//                                            "     path['/'] : {\n"
//                                            "        root : '/user/public/www'\n"
//                                            "     \n}"
//                                            "}");

/*
StringReader* reader = new StringReader("{\n"
                                        "\thttp[80] : {\n"
                                        "\t\tserver['8080'] : {\n"
                                        "\t\t\troot : /User/public/wwww,\n"
                                        "\t\t    access : {\n"
                                        "\t\t    \tallow : [0.0.0.1],\n"
                                        "\t\t    \tallow : [0.0.0.2],\n"
                                        "\t\t    \tallow : [0.0.0.3],\n"
                                        "\t\t    \tdeny :  [1.0.0.0],\n"
                                        "\t\t    \tdeny :  [2.0.0.0],\n"
                                        "\t\t    \tdeny :  [2.0.0.0]\n"
                                        "\t\t    },\n"
                                        "\n"
                                        "\n"
                                        " \t\taccess : {\n"
                                        "\t\t        allow : [3.0.0.1],\n"
                                        "\t\t        allow : [3.0.0.2],\n"
                                        "\t\t        allow : [3.0.0.3],\n"
                                        "\t\t        deny :  [4.0.0.0],\n"
                                        "\t\t        deny :  [4.0.0.0],\n"
                                        "\t\t        deny :  [5.0.0.0]\n"
                                        "\t\t    },\n"
                                        "\n"
                                        "\n"
                                        "\t\t    mimes : [\n"
                                        "\t\t\t\t\t   (htm, text/html),\n"
                                        "\t\t\t\t\t   (text, text/plain),\n"
                                        "\t\t\t\t\t   (css, text/css),\n"
                                        "\t\t\t\t\t   (xml, text/xml)\n"
                                        "\t\t\t\t\t]\n"
                                        "\n"
                                        "\t\t\tmimes : [\n"
                                        "\t\t\t   (htm, text/html),\n"
                                        "\t\t\t   (text, text/plain),\n"
                                        "\t\t\t   (css, text/css),\n"
                                        "\t\t\t   (xml, text/xml)\n"
                                        "\t\t\t]\n"
                                        "\n"
                                        "\t\t\tdomain['www.potalab'] : {\n"
                                        "\t\t\t    mimes : [\n"
                                        "\t\t\t        (a, text/html),\n"
                                        "\t\t\t        (b, text/plain),\n"
                                        "\t\t\t        (c, text/css),\n"
                                        "\t\t\t        (d, text/xml)\n"
                                        "\t\t\t            ]\n"
                                        "\t\t\t    mimes : [\n"
                                        "\t\t\t        (e, text/html),\n"
                                        "\t\t\t        (f, text/plain),\n"
                                        "\t\t\t        (g, text/css),\n"
                                        "\t\t\t        (h, text/xml)\n"
                                        "\t\t\t            ]\n"
                                        "\t\t\t} # domain [\n"
                                        "\t\t\tdomain['www.test.com'] : {\n"
                                        "\t\t\t    mimes : [\n"
                                        "\t\t\t        (1a, text/html),\n"
                                        "\t\t\t        (1b, text/plain),\n"
                                        "\t\t\t        (1c, text/css),\n"
                                        "\t\t\t        (1d, text/xml)\n"
                                        "\t\t\t            ]\n"
                                        "\t\t\t    mimes : [\n"
                                        "\t\t\t        (1e, text/html),\n"
                                        "\t\t\t        (1f, text/plain),\n"
                                        "\t\t\t        (1g, text/css),\n"
                                        "\t\t\t        (1h, text/xml)\n"
                                        "\t\t\t            ]\n"
                                        "\t\t\t} # domain [\n"
                                        "\t\t\tdomain['www.dalcomlab.com'] : {\n"
                                        "\t\t\t    location['/'] : {\n"
                                        "\t\t\t        root : 'user/www/public/',\n"
                                        "\t\t\t        mimes : [\n"
                                        "\t\t\t            (T1, text/html),\n"
                                        "\t\t\t            (T2, text/plain),\n"
                                        "\t\t\t            (T3, text/css),\n"
                                        "\t\t\t            (T3, text/xml)\n"
                                        "\t\t\t        ]\n"
                                        "\t\t\t    } # location\n"
                                        "\t\t\t    location['=/images/'] : {\n"
                                        "\t\t\t        root : 'user/www/public/image',\n"
                                        " \t\t        method : {\n"
                                        "\t\t                allow : GET,\n"
                                        "\t\t                allow : [GET, POST],\n"
                                        "\t\t                deny : TRACE,\n"
                                        "\t\t                allow : OPTIONS,\n"
                                        "\t\t                deny :  all\n"
                                        "\t\t            }\n"
                                        "\t\t\t        header : [\n"
                                        "\t\t\t            ('X-Forward-For', 'Test1'),\n"
                                        "\t\t\t            ('X-Forward-Proto', 'https'),\n"
                                        "\t\t\t            ('X-Real_Ip', '123.123.123.0')\n"
                                        "\t\t\t        ]\n"
                                        "\t\t\t        header : [\n"
                                        "\t\t\t            ('YY-Forward-For', 'Test1'),\n"
                                        "\t\t\t            ('YY-Forward-Proto', 'https'),\n"
                                        "\t\t\t            ('YY-Real_Ip', '123.123.123.0'),\n"
                                        "\t\t\t            ('BigHeader', \"\"\"\n"
                                        "\t\t\t             A\n"
                                        "\t\t\t             B\n"
                                        "\t\t\t             \"C\"\n"
                                        "\t\t\t             C\n"
                                        "\t\t\t            \"\"\")\t\t\t        ]\n"
                                        "\t\t\t    } # location\n"
                                        "\t\t\t} # domain [\n"
                                        "\t\t} #server\n"
                                        "\t} #http\n"
                                        "} #root");
*/
    StringReader* reader = new StringReader("{"
                                            "http[\"80\"] : {\n"
                                            "    domain[\"localhost\"] : {\n"
                                            "        path[\"/\"] : {\n"
                                            "            rewrite(\"^/user/\\w+\", \"/hello\")\n"
                                            "            return(\"You are not user.\")\n"
                                            "        }\n"
                                            "\n"
                                            "        path[\"/hello\"] : {\n"
                                            "            return(\"Hello, User.\")\n"
                                            "        }\n"
                                            "    }\n"
                                            "}"
                                            "}");
    TokenQueue queue;
    TokenBuilder::build(reader, &queue);

//    TokenIterator* iterator = queue.iterator();
//    while(iterator->more()) {
//        Token* token = iterator->next();
//        std::cout << token->text() << std::endl;
//    }

//    Token* root = queue.peek();
//    std::cout << root << std::endl;
//
//    ObjectParser object_parser(queue.iterator());
//    ConfigValue *obj = object_parser.parse();
//
//    std::cout << obj << std::endl;
//    obj->visit([](ConfigValue *name, ConfigValue *value) -> void {
//        if (name != nullptr) {
//            std::cout << name->text() << ":";
//        }
//
//        if (value != nullptr) {
//            std::cout << value->text();
//        }
//
//        std::cout << std::endl;
//    });


//
//    ObjectValue *value = new ObjectValue();
//    value->addField(new TextValue("a"), new TextValue("a"));
//    value->addField(new TextValue("b"), new TextValue("b"));
//    value->addField(new TextValue("b"), new TextValue("b"));
//    value->each([](ConfigValue *a, ConfigValue *b) -> void {
//        std::cout << "-------------" << std::endl;
//        std::cout << a->text() << std::endl;
//        std::cout << b->text() << std::endl;
//    });

 //   testHttpParser2();

    Listener *listener = new Listener();
    listener->start();

//    testHttpParser2();

//    std::string sp("geeksforgeeks");
//    std::regex re("(geeks)(.*)");
//
//    // flag type for determining the matching behavior
//    // && here it is for matches on strings.
//    std::smatch match;
//
//    // we can use member function on match
//    // to extract the matched pattern.
//    if (regex_search(sp, match, re) == true) {
//
//        // The size() member function indicates the
//        // number of capturing groups plus one for the overall match
//        // match size = Number of capturing group + 1
//        // (.*) which "forgeeks" ).
//        std::cout << "Match size = " << match.size() << std::endl;
//
//        // Capturing group is index from 0 to match_size -1
//        // .....here 0 to 2
//        // pattern at index 0 is the overall match "geeksforgeeks"
//        // pattern at index 1 is the first capturing group "geeks"
//        // pattern at index 2 is the 2nd capturing group "forgeeks"
//
//        std::cout << "Whole match : " << match.str(0) << std::endl;
//        std:: cout << "First capturing group is '" << match.str(1)
//             << "' which is captured at index " << match.position(1)
//             << std::endl;
//        std::cout << "Second capturing group is '" << match.str(2)
//             << "' which is captured at index " << match.position(2)
//             << std::endl;
//    }
//    else {
//        std::cout << "No match is found" << std::endl;
//    }

    return 0;
}


void testHttpHeaderParser() {
    std::string data = "authority: apis.google.com\r\n"
                       "method: GET\r\n"
                       "path: /_/scs/abc-static/_/js/k=gapi.gapi.en.7yBiF1UUXzY.O/m=gapi_iframes,googleapis_client/rt=j/sv=1/d=1/ed=1/rs=AHpOoo-pEDm0pqtBuZIKGpxOGTcQloIhJw/cb=gapi.loaded_0\r\n"
                       "scheme: https\r\n"
                       "accept: */*\r\n"
                       "accept-encoding: gzip, deflate, br\r\n"
                       "accept-language: ko-KR,ko;q=0.9,en-US;q=0.8,en;q=0.7,fr;q=0.6,ja;q=0.5,zh-TW;q=0.4,zh;q=0.3\r\n"
                       "cache-control: no-cache\r\n"
                       "pragma: no-cache\r\n"
                       "referer: https://www.google.com/\r\n"
                       "sec-ch-ua: \" Not;A Brand\";v=\"99\", \"Google Chrome\";v=\"91\", \"Chromium\";v=\"91\"\r\n"
                       "sec-ch-ua-mobile: ?0\r\n"
                       "sec-fetch-dest: script\r\n"
                       "sec-fetch-mode: no-cors\r\n"
                       "sec-fetch-site: same-site\r\n";

    HttpHeader header;
    HttpHeaderParser parser;
    parser.parse(data.c_str(), (int)data.length(), header);

    auto names = header.getHeaderNames();
    for_each(names.begin(), names.end(), [&](auto name) {
        std::cout << name << " --> " << header.getHeader(name) << std::endl;
    });
}

void testHttpParser() {
    HttpRequestParser *parser = new HttpRequestParser();
    std::string line = "    GET      /test.jsp?a=a&b=b       HTTP/1.1\r\n";
    HttpRequest request;
    parser->parse(line.c_str(), (int)line.length(), request);
    std::cout << "method : " << request.getMethod() << std::endl;
    std::cout << "uri : " << request.getUri() << std::endl;
    std::cout << "query string : " << request.getQueryString() << std::endl;
    std::cout << "version : " << request.getVersion() << std::endl;

}

void testHttpParser2() {
    HttpRequestParser *parser = new HttpRequestParser();
    std::string data =  "    GET      /test.jsp?a=a&b=b       HTTP/1.1\r\n"
                        "authority: apis.google.com\r\n"
                       "method: GET\r\n"
                       "path: /_/scs/abc-static/_/js/k=gapi.gapi.en.7yBiF1UUXzY.O/m=gapi_iframes,googleapis_client/rt=j/sv=1/d=1/ed=1/rs=AHpOoo-pEDm0pqtBuZIKGpxOGTcQloIhJw/cb=gapi.loaded_0\r\n"
                       "scheme: https\r\n"
                       "accept: */*\r\n"
                       "accept-encoding: gzip, deflate, br\r\n"
                       "accept-language: ko-KR,ko;q=0.9,en-US;q=0.8,en;q=0.7,fr;q=0.6,ja;q=0.5,zh-TW;q=0.4,zh;q=0.3\r\n"
                       "cache-control: no-cache\r\n"
                       "pragma: no-cache\r\n"
                       "referer: https://www.google.com/\r\n"
                       "sec-ch-ua: \" Not;A Brand\";v=\"99\", \"Google Chrome\";v=\"91\", \"Chromium\";v=\"91\"\r\n"
                       "sec-ch-ua-mobile: ?0\r\n"
                       "sec-fetch-dest: script\r\n"
                       "sec-fetch-mode: no-cors\r\n"
                       "sec-fetch-site: same-site\r\n\r\n";

    HttpRequest request;
    parser->parse(data.c_str(), (int)data.length(), request);
    std::cout << "method : " << request.getMethod() << std::endl;
    std::cout << "uri : " << request.getUri() << std::endl;
    std::cout << "query string : " << request.getQueryString() << std::endl;
    std::cout << "version : " << request.getVersion() << std::endl;

    auto names = request.getHeader()->getHeaderNames();
    for_each(names.begin(), names.end(), [&](auto name) {
        std::cout << name << " --> " << request.getHeader()->getHeader(name) << std::endl;
    });
}