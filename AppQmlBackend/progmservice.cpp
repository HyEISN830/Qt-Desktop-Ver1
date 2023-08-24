#include "progmservice.h"

ProgmService::ProgmService()
{

}

void ProgmService::closethreadpool()
{
    QThreadPool::globalInstance()->clear();
    QThreadPool::globalInstance()->waitForDone(1000);
}
