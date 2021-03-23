#ifndef ABSTRACT_OPERATION_H
#define ABSTRACT_OPERATION_H
#include <string>
#include <asio/ip/tcp.hpp>

#include "dllexport.h"

namespace operation
{
    CPP_LIBRARY_API class AbstractOperation
    {
    public:
        AbstractOperation() = default;
        virtual ~AbstractOperation() = default;
    protected:
        AbstractOperation(const AbstractOperation&) = default;
        AbstractOperation(AbstractOperation&&) = default;
        AbstractOperation& operator=(const AbstractOperation&) = default;
        AbstractOperation& operator=(AbstractOperation&&) = default;
    public:
        virtual void readStream(asio::ip::tcp::iostream& stream) {}
        virtual void execute(asio::ip::tcp::iostream& stream) = 0;
        virtual std::string getCommand() = 0;
        virtual void init() {}
    protected:
        std::string prompt(const std::string message = "") { return this->getCommand() + "> " + message; }
    };

    CPP_LIBRARY_API class AbstractOperationCreator
    {
    public:
        AbstractOperationCreator() = default;
        virtual ~AbstractOperationCreator() = default;
    protected:
        AbstractOperationCreator(const AbstractOperationCreator&) = default;
        AbstractOperationCreator(AbstractOperationCreator&&) = default;
        AbstractOperationCreator& operator=(const AbstractOperationCreator&) = default;
        AbstractOperationCreator& operator=(AbstractOperationCreator&&) = default;
    public:
        virtual std::unique_ptr<AbstractOperation> create() = 0;
        virtual std::string getIdentifier() = 0;
    };
} // namespace operation
#endif // ABSTRACT_OPERATION_H
