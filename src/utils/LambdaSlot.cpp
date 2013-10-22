/*
 * LambdaSlot.cpp

 *
 *  Created on: Oct 14, 2013
 *      Author: mvaldenegro
 */

#include "LambdaSlot.h"

LambdaSlot::LambdaSlot(std::function<void ()> lambda, QObject* parent)
: QObject(parent), mLambda(lambda)
{
}
