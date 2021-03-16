#pragma once
#ifndef OPERATION_FACTORY_H
#define OPERATION_FACTORY_H
#include <map>
#include <memory>
#include <string>
#include "abstract_operation.h"

namespace factory
{
	CPP_LIBRARY_API class OperationFactory
	{
	private:
		std::map<const std::string, std::unique_ptr<operation::AbstractOperationCreator>> operations_;

	public:
		template<typename operationType>
		void registerOperation()
		{
			static_assert(std::is_convertible<operationType*, operation::AbstractOperationCreator*>::value,
				"This function can only construct concrete subclasses of operation::AbstractOperation");

			std::unique_ptr<operation::AbstractOperationCreator> creator = std::make_unique<operationType>();
			const std::string identifier = creator->getIdentifier();
			operations_.try_emplace(identifier, std::move(creator));
		}

		std::unique_ptr<operation::AbstractOperation> get(const std::string& identifier)
		{
			if (operations_.count(identifier) == 0)
			{
				return nullptr;
			}
			
			return operations_.at(identifier)->create();
		}
	};
} // namespace factory
#endif // OPERATION_FACTORY_H
