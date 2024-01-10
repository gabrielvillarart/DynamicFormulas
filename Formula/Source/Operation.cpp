#include "Operation.h"
#include "OperandBuffer.h"

FOperand FOperation::operator()(FOperandBuffer& Operands) const
{
    return Function(Operands);
}

FOperand FOperations::NoneFunction(FOperandBuffer& OutOperands)
{ return FOperand();
}

FOperand FOperations::LessThanFunction(FOperandBuffer& OutOperands)
{ return FOperand();
}

FOperand FOperations::GreaterThanFunction(FOperandBuffer& OutOperands)
{ return FOperand();
}

FOperand FOperations::LessEqualThanFunction(FOperandBuffer& OutOperands)
{ return FOperand();
}

FOperand FOperations::GreaterEqualThanFunction(FOperandBuffer& OutOperands)
{ return FOperand();
}

FOperand FOperations::EqualToFunction(FOperandBuffer& OutOperands)
{ return FOperand();
}

FOperand FOperations::NotEqualToFunction(FOperandBuffer& OutOperands)
{ return FOperand();
}

FOperand FOperations::MaximumFunction(FOperandBuffer& OutOperands)
{ return FOperand();
}

FOperand FOperations::MinimumFunction(FOperandBuffer& OutOperands)
{ return FOperand();
}

FOperand FOperations::AverageFunction(FOperandBuffer& OutOperands)
{ return FOperand();
}

FOperand FOperations::SignFunction(FOperandBuffer& OutOperands)
{ return FOperand();
}

FOperand FOperations::NegationFunction(FOperandBuffer& OutOperands)
{ 
	auto A = OutOperands.Pull().Get<double>();

	return FOperand(-A);
}

FOperand FOperations::AbsoluteFunction(FOperandBuffer& OutOperands)
{ return FOperand();
}

FOperand FOperations::GetNegativeFunction(FOperandBuffer& OutOperands)
{ return FOperand();
}

FOperand FOperations::RoundFunction(FOperandBuffer& OutOperands)
{ return FOperand();
}

FOperand FOperations::RoofFunction(FOperandBuffer& OutOperands)
{ return FOperand();
}

FOperand FOperations::FloorFunction(FOperandBuffer& OutOperands)
{ return FOperand();
}

FOperand FOperations::TruncateFunction(FOperandBuffer& OutOperands)
{ return FOperand();
}

FOperand FOperations::AdditionFunction(FOperandBuffer& OutOperands)
{
	auto B = OutOperands.Pull().Get<double>();
	auto A = OutOperands.Pull().Get<double>();

	return FOperand(A+B);
}

FOperand FOperations::SubtractionFunction(FOperandBuffer& OutOperands)
{
	auto B = OutOperands.Pull().Get<double>();
	auto A = OutOperands.Pull().Get<double>();

	return FOperand(A-B);
}

FOperand FOperations::MultiplicationFunction(FOperandBuffer& OutOperands)
{
	auto B = OutOperands.Pull().Get<double>();
	auto A = OutOperands.Pull().Get<double>();

	return FOperand(A*B);
}

FOperand FOperations::DivisionFunction(FOperandBuffer& OutOperands)
{
	auto B = OutOperands.Pull().Get<double>();
	auto A = OutOperands.Pull().Get<double>();

	return FOperand(A/B);
}

FOperand FOperations::ModuloFunction(FOperandBuffer& OutOperands)
{ return FOperand();
}

FOperand FOperations::RemainderFunction(FOperandBuffer& OutOperands)
{ return FOperand();
}

FOperand FOperations::ExponentiationFunction(FOperandBuffer& OutOperands)
{ return FOperand();
}

FOperand FOperations::SquareFunction(FOperandBuffer& OutOperands)
{ 
	auto A = OutOperands.Pull().Get<double>();

	return FOperand(A * A);
}

FOperand FOperations::SquareRootFunction(FOperandBuffer& OutOperands)
{ return FOperand();
}

FOperand FOperations::CubicRootFunction(FOperandBuffer& OutOperands)
{ return FOperand();
}

FOperand FOperations::SineFunction(FOperandBuffer& OutOperands)
{ return FOperand();
}

FOperand FOperations::CosineFunction(FOperandBuffer& OutOperands)
{ return FOperand();
}

FOperand FOperations::TangentFunction(FOperandBuffer& OutOperands)
{ return FOperand();
}

FOperand FOperations::SecantFunction(FOperandBuffer& OutOperands)
{ return FOperand();
}

FOperand FOperations::CosecantFunction(FOperandBuffer& OutOperands)
{ return FOperand();
}

FOperand FOperations::CotangentFunction(FOperandBuffer& OutOperands)
{ return FOperand();
}

FOperand FOperations::ArcsineFunction(FOperandBuffer& OutOperands)
{ return FOperand();
}

FOperand FOperations::ArccosineFunction(FOperandBuffer& OutOperands)
{ return FOperand();
}

FOperand FOperations::ArctangentFunction(FOperandBuffer& OutOperands)
{ return FOperand();
}

FOperand FOperations::ArcsecantFunction(FOperandBuffer& OutOperands)
{ return FOperand();
}

FOperand FOperations::ArccosecantFunction(FOperandBuffer& OutOperands)
{ return FOperand();
}

FOperand FOperations::ArccotangentFunction(FOperandBuffer& OutOperands)
{ return FOperand();
}

FOperand FOperations::LinearInterpolationFunction(FOperandBuffer& OutOperands)
{ return FOperand();
}

FOperand FOperations::MapRangeFunction(FOperandBuffer& OutOperands)
{ return FOperand();
}