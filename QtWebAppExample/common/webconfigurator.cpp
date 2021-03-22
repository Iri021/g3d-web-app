#include "webconfigurator.h"


WebConfigurator::WebConfigurator(QString &configPath) :
    m_configPath(configPath),
    m_config(m_configPath),
    m_httpListener(&m_config, this)
{
    /* Put objects of all dynamic pages into QHash,
     * to be used on our web server
     * */
    m_pages.insert("/index.html", new IndexPage());             // Print/index
    m_pages.insert("/second.html", new SecondPage());           // Settings
    m_pages.insert("/first.html", new FirstPage());             // Control
    m_pages.insert("/printinfo.html", new PrintInfoPage());     // PrintInfo
    m_pages.insert("/printing.html", new PrintingPage());       // Printing

    /* For the controller of static files
     *  you need to refer to the settings object, go to the group
     *  controller settings and create a new controller
     *  using the state of the settings object set to the group
     *  static file controller parameters
     * */
    m_config.beginGroup("html-static");
    m_staticFileController = new StaticFileController(&m_config);
    m_config.endGroup();
}

WebConfigurator::~WebConfigurator()
{
    foreach(WebConfiguratorPage* page, m_pages) {
        delete page;
    }
    delete m_staticFileController;
}

void WebConfigurator::service(HttpRequest &request, HttpResponse &response)
{
    /* This method checks the request address
     *  for compliance with existing pages.
     *  In this case, if the page exists, then we
     * оwe refer to the page object and send the request for further processing.
     *  Otherwise, return a 404 error
     * */
    QByteArray path = request.getPath();
    for(auto i = m_pages.begin(); i != m_pages.end(); ++i) {
        if(path.startsWith(i.key().toLatin1())) {
            return i.value()->handleRequest(request,response);
        }
    }
    if (path=="/"){
        response.redirect("/index.html");
        return;
    }
}
