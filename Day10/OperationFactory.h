#pragma once

#include <string_view>
#include <memory>

#include "NoOp.h"
#include "Addx.h"

std::unique_ptr<Operation> MakeOperation(std::string_view op);