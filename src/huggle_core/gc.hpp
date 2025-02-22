// IMPORTANT: this file has a different license than rest of huggle

//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU Lesser General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU Lesser General Public License for more details.

// Copyright (c) Petr Bena 2014

#ifndef GC_H
#define GC_H

#include "definitions.hpp"

#include <QList>

class QMutex;

constexpr int HUGGLECONSUMER_WIKIEDIT                 = 0;
constexpr int HUGGLECONSUMER_QUEUE                    = 1;
constexpr int HUGGLECONSUMER_CORE_POSTPROCESS         = 2;
constexpr int HUGGLECONSUMER_EDITQUERY                = 3;
constexpr int HUGGLECONSUMER_REVERTQUERY              = 4;
constexpr int HUGGLECONSUMER_MESSAGE_SEND             = 5;
constexpr int HUGGLECONSUMER_HISTORYWIDGET            = 6;
//! This is used to lock the message resource before it's passed to parent object
constexpr int HUGGLECONSUMER_CORE_MESSAGE             = 7;
constexpr int HUGGLECONSUMER_PROCESSOR                = 8;
constexpr int HUGGLECONSUMER_MAINPEND                 = 9;
constexpr int HUGGLECONSUMER_QP                       = 10;
constexpr int HUGGLECONSUMER_QP_UNCHECKED             = 11;
constexpr int HUGGLECONSUMER_QP_REVERTBUFFER          = 12;
constexpr int HUGGLECONSUMER_QP_WATCHLIST             = 17;
constexpr int HUGGLECONSUMER_MAINFORM_HISTORICAL      = 13;
constexpr int HUGGLECONSUMER_QP_MODS                  = 14;
constexpr int HUGGLECONSUMER_REVERTQUERYTMR           = 16;
constexpr int HUGGLECONSUMER_CALLBACK                 = 20;
constexpr int HUGGLECONSUMER_PYTHON                   = 60;
constexpr int HUGGLECONSUMER_JS_POOL                  = 100;
constexpr int HUGGLECONSUMER_CORE                     = 800;

// some macros so that people hate us
#define GC_DECREF(collectable) if (collectable) collectable->DecRef(); collectable=nullptr
#define GC_DECNAMEDREF(collectable, consumer) if(collectable) collectable->UnregisterConsumer(consumer); collectable=nullptr
constexpr int GC_LIMIT = 60;

namespace Huggle
{
    class Collectable;
    class GC_t;

    //! Garbage collector that can be used to collect some objects

    //! Every object must be derived from Collectable, otherwise it
    //! must not be handled by garbage collector
    class HUGGLE_EX_CORE GC
    {
        public:
            /*!
             * \brief Collect will safely decrement a reference of an object and set the pointer to NULL
             * \param object
             */
            //static void Collect(Collectable **object);
            //static void Collect(Collectable **object, int ConsumerID);
            static GC *gc;

            GC();
            ~GC();
            //! Function that walks through the list and delete these that can be deleted
            void DeleteOld();
            void Start();
            void Stop();
            bool IsRunning();
            //! List of all managed queries that qgc keeps track of
            QList<Collectable*> list;
            //! QMutex that is used to lock the GC::list object

            //! This lock needs to be aquired every time when you need to access this list
            //! from any thread during runtime
            QMutex * Lock;
        private:
            GC_t *gc_t;
    };
}

#endif // GC_H
