#ifndef THREADSLEEP_H
#define THREADSLEEP_H

class SleeperThread : public QThread
{
public:
  static void msleep(unsigned long msecs)
   {
      QThread::msleep(msecs);
   }
};

#endif // THREADSLEEP_H
