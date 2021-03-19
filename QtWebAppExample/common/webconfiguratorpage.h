#ifndef WEBCONFIGURATORPAGE_H
#define WEBCONFIGURATORPAGE_H

#include <QObject>
#include <httprequesthandler.h>
#include <httplistener.h>
#include <template.h>

class WebConfiguratorPage : public QObject
{
    Q_OBJECT
public:
    WebConfiguratorPage(const QString& title);
    virtual void handleRequest(HttpRequest&, HttpResponse&) {}
    virtual ~WebConfiguratorPage() {}

protected:
    Template commonTemplate() const;

private:
    QString m_title;
};





class IndexPage : public WebConfiguratorPage
{
    Q_OBJECT
public:
    IndexPage() : WebConfiguratorPage("G3D T2000") {}

    virtual ~IndexPage() {}
public:
    virtual void handleRequest(HttpRequest &request, HttpResponse &response) override;
};





class FirstPage : public WebConfiguratorPage
{
    Q_OBJECT
public:
    FirstPage() : WebConfiguratorPage("G3D T2000") {}

    virtual ~FirstPage() {}
public:
    virtual void handleRequest(HttpRequest &request, HttpResponse &response) override;
};





class SecondPage : public WebConfiguratorPage
{
    Q_OBJECT
public:
    SecondPage() : WebConfiguratorPage("G3D T2000") {}

    virtual ~SecondPage() {}
public:
    virtual void handleRequest(HttpRequest &request, HttpResponse &response) override;
};





class PrintInfoPage : public WebConfiguratorPage
{
    Q_OBJECT
public:
    PrintInfoPage() : WebConfiguratorPage("G3D T2000") {}

    virtual ~PrintInfoPage() {}
public:
    virtual void handleRequest(HttpRequest &request, HttpResponse &response) override;
};


class PrintingPage : public WebConfiguratorPage
{
    Q_OBJECT
public:
    PrintingPage() : WebConfiguratorPage("G3D T2000") {}

    virtual ~PrintingPage() {}
public:
    virtual void handleRequest(HttpRequest &request, HttpResponse &response) override;
};



#endif // WEBCONFIGURATORPAGE_H
