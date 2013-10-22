/*
 * LambdaSlot.h
 *
 *  Created on: Oct 14, 2013
 *      Author: mvaldenegro
 */

#ifndef LAMBDASLOT_H_
#define LAMBDASLOT_H_

#include <functional>
#include <QObject>

class LambdaSlot : public QObject
{
    Q_OBJECT

    public:
        LambdaSlot(std::function<void ()> lambda, QObject* parent = 0);

    public slots:
        void call()
        {
            if(mLambda) {
                mLambda();
            }
        }

    private:
        std::function<void()> mLambda;

};



#endif /* LAMBDASLOT_H_ */
