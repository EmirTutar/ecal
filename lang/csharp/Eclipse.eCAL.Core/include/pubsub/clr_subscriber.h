/* ========================= eCAL LICENSE =================================
 *
 * Copyright (C) 2016 - 2025 Continental Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * ========================= eCAL LICENSE =================================
*/

#pragma once

/**
 * @file  clr_subscriber.h
**/

#include "config/clr_subscriber.h"
#include "pubsub/clr_types.h"

#include <ecal/pubsub/subscriber.h>


namespace Eclipse {
  namespace eCAL {
    namespace Core {

      /**
       * @brief Managed wrapper for the native eCAL::CSubscriber class.
       *
       * This class provides methods to receive messages over eCAL and query subscriber information.
       */
      public ref class Subscriber
      {
      public:
        /**
         * @brief Constructs a Subscriber with the given topic name.
         *
         * @param topicName Unique topic name.
         */
        Subscriber(System::String^ topicName) : Subscriber(topicName, nullptr, nullptr, nullptr) {}

        /**
         * @brief Constructs a Subscriber with the given topic name and data type information.
         *
         * @param topicName Unique topic name.
         * @param dataTypeInfo Topic data type information.
         */
        Subscriber(System::String^ topicName, DataTypeInformation^ dataTypeInfo) : Subscriber(topicName, dataTypeInfo, nullptr, nullptr) {}

        /**
         * @brief Constructs a Subscriber with the given topic name, data type information, and an event callback.
         *
         * @param topicName Unique topic name.
         * @param dataTypeInfo Topic data type information.
         * @param eventCallback Optional subscriber event callback.
         */
        Subscriber(System::String^ topicName, DataTypeInformation^ dataTypeInfo, SubscriberEventCallbackDelegate^ eventCallback) : Subscriber(topicName, dataTypeInfo, eventCallback, nullptr) {};
        
        /**
         * @brief Constructs a Subscriber with the given topic name, data type information, event callback and config.
         *
         * @param topicName Unique topic name.
         * @param dataTypeInfo Topic data type information.
         * @param eventCallback Optional subscriber event callback.
         * @param config Optional subscriber configuration
         */
        Subscriber(System::String^ topicName, DataTypeInformation^ dataTypeInfo, SubscriberEventCallbackDelegate^ eventCallback, Config::SubscriberConfiguration^ config);

        /**
         * @brief Destructor.
         */
        ~Subscriber();

        /**
         * @brief Finalizer.
         */
        !Subscriber();

        /**
         * @brief Sets or overwrites the receive callback.
         *
         * @param callback The callback function to set.
         */
        void SetReceiveCallback(ReceiveCallbackDelegate^ callback);

        /**
         * @brief Removes the receive callback.
         */
        void RemoveReceiveCallback();

        /**
         * @brief Queries the number of connected publishers.
         *
         * @return The number of connected publishers.
         */
        int GetPublisherCount();

        /**
         * @brief Retrieves the topic name.
         *
         * @return The topic name as a System::System::String^.
         */
        System::String^ GetTopicName();

        /**
         * @brief Retrieves the topic identifier.
         *
         * @return An instance of TopicId containing the topic id details.
         */
        TopicId^ GetTopicId();

        /**
         * @brief Retrieves the topic data type information.
         *
         * @return An instance of DataTypeInformation containing the data type details.
         */
        DataTypeInformation^ GetDataTypeInformation();

      private:
        /**
         * @brief Pointer to the native CSubscriber instance.
         */
        ::eCAL::CSubscriber* m_native_subscriber;

        /**
         * @brief Stored managed callback to prevent garbage collection.
         */
        ReceiveCallbackDelegate^ m_receiveCallback;
      };

    } // namespace Core
  } // namespace eCAL
} // namespace Eclipse
