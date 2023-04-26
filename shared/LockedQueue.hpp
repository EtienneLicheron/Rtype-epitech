/*
** EPITECH PROJECT, 2022
** B-CPP-500-MPL-5-1-rtype-benjamin.vic
** File description:
** LockedQueue
*/

#ifndef LOCKEDQUEUE_HPP_
#define LOCKEDQUEUE_HPP_

#include <mutex>
#include <queue>
#include <list>

namespace RType
{
    namespace Shared
    {
        template <typename T>
        class LockedQueue
        {
        public:
            void push(T &value)
            {
                std::lock_guard<std::mutex> lock(_mutex);
                _queue.push(value);
            }

            T pop()
            {
                std::lock_guard<std::mutex> lock(_mutex);
                T value = _queue.front();
                _queue.pop();
                return value;
            }

            bool empty()
            {
                std::lock_guard<std::mutex> lock(_mutex);
                return _queue.empty();
            }

        private:
            std::mutex _mutex;
            std::queue<T> _queue;
        };
    }
}

#endif /* !LOCKEDQUEUE_HPP_ */
