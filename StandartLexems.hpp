#pragma once

#include "Defines.hpp"
#include "LexemePluginLoader.hpp"
#include "Expression.hpp"

//UnspecifiedMinus class. Represents token of minus operation, which must be specifyed later ether as a infix operation, or unar operation.
class UnspecifiedMinus : public UnspecifiedOperationToken
{
private:
	std::shared_ptr<PrefixOperationToken> unarMinusToken;
	std::shared_ptr<InfixOperationToken> binarMinusToken;
public:
	UnspecifiedMinus();
	OperationToken* specify(ExpressionItem* left, ExpressionItem* right) override;
};

//Local plugin, that contains standart lexem set
void StandartLexemsImporter(LexemeVec& lexemeVec);