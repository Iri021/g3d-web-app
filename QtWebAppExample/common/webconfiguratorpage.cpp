#include "webconfiguratorpage.h"
#include <QFile>
#include <QDebug>
#include <QCoreApplication>

WebConfiguratorPage::WebConfiguratorPage(const QString &title) :
    m_title(title)
{

}

Template WebConfiguratorPage::commonTemplate() const
{
    /* The common.htm file is used to form the main template.
     * The page title is set in it ...
     * */
    QFile file(":/html/common.htm");
    Template common(file, QTextCodec::codecForName("UTF-8"));
    common.setVariable("Title", m_title);

    /* And the menu is also formed.
     * Formation of the menu is done taking into account the check for,
     * whether this menu is required on the page or not.
     * the menu will be on all pages, so
     * just indicate the need for this menu.
     * If you look at the contents of the common.htm file, then
     * find there a check for the "Navigation" parameter
     * */
    bool navigation = true;
    common.setCondition("Navigation", navigation);
    if(navigation) {
        /* And the menu itself will be formed using a cyclic addition
         *  points, which is also reflected by a special construction in the  common.htm file
         * */
        common.loop("Items", 4);

        common.setVariable("Items0.href", "/index.html");
        common.setVariable("Items0.name", "Print");

        common.setVariable("Items1.href", "/first.html");
        common.setVariable("Items1.name", "Control");

        common.setVariable("Items2.href", "/second.html");
        common.setVariable("Items2.name", "Settings");

        common.setVariable("Items3.href", "/printinfo.html");
        common.setVariable("Items3.name", "PrintInfo");

        common.setVariable("Items4.href", "/printing.html");
        common.setVariable("Items4.name", "printing");
    }
    return common;
}

/* Next comes the implementation of the request handler for each of the pages.
  * In fact, they are identical in this example, but in a real application
  * will most likely differ in their logic
  * */

void IndexPage::handleRequest(HttpRequest &request, HttpResponse &response)
{

    qDebug() << "[DEBUG] " << "Function call " << "IndexPage::handleRequest(HttpRequest &request, HttpResponse &response)";


    if (request.getMethod() == "GET")
    {
        // Get the parent page template
        Template common = commonTemplate();
        QFile file(":/html/index.htm");
        Template contents(file, QTextCodec::codecForName("UTF-8"));
        /* Then we add our own content from the template for this page
                  * in the parent template, a place to add information, as well as another template
                  * in this example denoted as {Content}
                  * */

        common.setVariable("Content", contents);
        response.setHeader("Content-Type", "text/html; charset=ISO-8859-1");
        response.write(common.toUtf8());
        return;
    }

    else
    {
        return;
    }
    return;
}

void FirstPage::handleRequest(HttpRequest &request, HttpResponse &response)
{
    if (request.getMethod() == "GET")
    {
        Template common = commonTemplate();
        QFile file(":/html/first.htm");
        Template contents(file, QTextCodec::codecForName("UTF-8"));
        common.setVariable("Content", contents);
        response.setHeader("Content-Type", "text/html; charset=ISO-8859-1");
        response.write(common.toUtf8());
        return;
    }
    else
    {
        return;
    }
    return;
}

void SecondPage::handleRequest(HttpRequest &request, HttpResponse &response)
{
    if (request.getMethod() == "GET")
    {
        Template common = commonTemplate();
        QFile file(":/html/second.htm");
        Template contents(file, QTextCodec::codecForName("UTF-8"));
        common.setVariable("Content", contents);
        response.setHeader("Content-Type", "text/html; charset=ISO-8859-1");
        response.write(common.toUtf8());
        return;
    }
    else
    {
        return;
    }
    return;    qDebug() << "[DEBUG] " << "Function call " << "IndexPage::handleRequest(HttpRequest &request, HttpResponse &response)";

}

void PrintInfoPage::handleRequest(HttpRequest &request, HttpResponse &response)
{
    if (request.getMethod() == "GET")
    {
        Template common = commonTemplate();
        QFile file(":/html/printinfo.html");
        Template contents(file, QTextCodec::codecForName("UTF-8"));
        common.setVariable("Content", contents);
        response.setHeader("Content-Type", "text/html; charset=ISO-8859-1");
        response.write(common.toUtf8());
        return;
    }
    else if (request.getMethod() == "POST")
    {
        // Perform the same thing above, except we will add the
        // getting the file uploaded.

        // Get the parent page template
        Template common = commonTemplate();
        QFile file(":/html/printinfo.html");
        Template contents(file, QTextCodec::codecForName("UTF-8"));
        /* Then we add our own content from the template for this page
                  * in the parent template, a place to add information, as well as another template
                  * in this example denoted as {Content}
                  * */

        common.setVariable("Content", contents);
        response.setHeader("Content-Type", "text/html; charset=ISO-8859-1");
        response.write(common.toUtf8());


        // Print filename.
        QString filename = request.getParameter("filename");
        qDebug() << "[DEBUG] " << "filename: " << filename;

        // Create temporary file.
        QTemporaryFile* uploaded_file_temp=request.getUploadedFile("filename");
        QString app_path = QCoreApplication::applicationDirPath();

        // Get file contents.
        QFile *outfile=new QFile(filename);
        outfile->open(QIODevice::WriteOnly);

        if (uploaded_file_temp)
        {
            qDebug() << "[DEBUG] " << "Uploaded file opened: " << filename;

            while (!uploaded_file_temp->atEnd() && !uploaded_file_temp->error())
            {
                QByteArray buffer=uploaded_file_temp->read(65536);
                outfile->write(buffer);
            }

        }

        outfile->close();

        return;

    }
}

void PrintingPage::handleRequest(HttpRequest &request, HttpResponse &response)
{
    if (request.getMethod() == "POST")
    {
        Template common = commonTemplate();
        QFile file(":/html/printing.html");
        Template contents(file, QTextCodec::codecForName("UTF-8"));
        common.setVariable("Content", contents);
        response.setHeader("Content-Type", "text/html; charset=ISO-8859-1");
        response.write(common.toUtf8());

        // Print filename.
        QString filename = request.getParameter("filename");
        qDebug() << "[DEBUG] " << "filename: " << filename;


        // Get file contents.
        QFile *outfile=new QFile(filename);
        outfile->open(QIODevice::WriteOnly);

    }

    else
    {
        return;
    }
    return;

}
