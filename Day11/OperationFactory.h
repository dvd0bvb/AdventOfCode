#pragma once

#include <string_view>
#include <memory>

#include "Operation.h"

std::unique_ptr<Operation> MakeOperation(std::string_view line);
