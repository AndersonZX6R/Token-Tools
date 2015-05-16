/***
 * TokenAnalisys.h
 *
 * Copyright(c) Eng.º Anderson Marques Ribeiro.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __TOKENANALISYS
#define __TOKENANALISYS

#ifdef _MANAGED
#pragma unmanaged
#endif // ifdef _MANAGED

#include <string>
#include <vector>
#include <map>
#include "TextTypes.h"
#include "..\Utils\Error.h"

#include "..\DataStorage\SymbolTable.h"

using namespace std;
using namespace DATASTORAGE;

namespace TEXTTOOLS
{

typedef long TokenIdentType;
const TokenIdentType TOKEN_IDENT_NULL = -1;

extern TokenIdentType lastIdentToken;

#define DECLARE_TOKEN_IDENT(Ident) const TokenIdentType Ident = lastIdentToken++

struct TokenConfigStruct
{
    bool ignore, appellant;
}; // struct TokenConfigStruct

struct TokenDataStruct
{
    string str;
	TokenIdentType ident;

    bool isToken()
	{
		return ident != TOKEN_IDENT_NULL;
	};
	
}; // struct TokenDataStruct

typedef vector<TokenDataStruct> TokenDataListType;

const TokenConfigStruct TOKEN_CONFIG_DEFAULT =
{
    false, false
};

const TokenDataStruct TOKEN_DATA_NULL =
{
	"", TOKEN_IDENT_NULL
};

DECLARE_ERROR_CODE(ERR_DUPLICATE_TOKEN);
DECLARE_ERROR_CODE(ERR_INVALID_TOKEN);
DECLARE_ERROR_CODE(ERR_DUPLICATE_IDENT);

BEGIN_DECLARE_ERROR(ETokenAnalisys)
    DECLARE_ERROR(ERR_DUPLICATE_TOKEN, "Token duplicado")
    DECLARE_ERROR(ERR_INVALID_TOKEN, "Token inválido")
	DECLARE_ERROR(ERR_DUPLICATE_IDENT, "Identificador de token duplicado")
END_DECLARE_ERROR;

/***
 * TokenAnalysisConfigStruct;
 *
 * Armazena valores de configuração utilizados por uma instância da classe TokenAnalysis.
 * ----
 */
struct TokenAnalysisConfigStruct
{
	// uniqueTokenId;
	//
	// Todo token adicionado a lista interna de TokenAnalysis tem um identificador associado a ele. Caso este parâmetro seja configurado como true,
	// ---- a classe é informada que não deve permitir que um mesmo identificador seja usado por mais de um token.
	// **************************************************************************************************************************************************
	bool uniqueTokenId;
}; // struct TokenAnalysisConfigStruct;

const TokenAnalysisConfigStruct TOKEN_ANALYSIS_CONFIG_PADRAO =
{
	false
};

class TokenAnalysis
{
public:

	TokenAnalysis(TokenAnalysisConfigStruct config = TOKEN_ANALYSIS_CONFIG_PADRAO) :
		m_taConfig(config)
	{};

private:

    typedef map<string, TokenDataStruct> MapTokenDataType;
	typedef map<TokenIdentType, TokenConfigStruct> MapTokenConfigType;

    MapTokenDataType
		m_mtiTokens;
	MapTokenConfigType
		m_mtcTokensConfig;
	TokenAnalysisConfigStruct
		m_taConfig;

public:

    long getTokenCount() const
    {
        return m_mtiTokens.size();
    };

    TokenConfigStruct getTokenConfig(const string &token)
    {
    MapTokenDataType::const_iterator
		it = m_mtiTokens.find(token);

        if (it == m_mtiTokens.end())
            RAISE(ETokenAnalisys, ERR_INVALID_TOKEN);

	TokenConfigStruct
		tc;

		tokenConfigByIdent(it->second.ident, &tc);

		return tc;
    };
	bool tokenConfigByIdent(TokenIdentType ident, TokenConfigStruct *config = NULL);

    // addToken;
    //
    // Adiciona um novo token na lista interna do analisador.
    // ----
    // *****************************************************************************************************************************************
    void addToken(TokenIdentType ident, const string &token, TokenConfigStruct def = TOKEN_CONFIG_DEFAULT);

	// breakString;
	//
	// Decompõe uma string em sub-strings, utilizando os tokens previamente adicionados no objeto como delimitação.
	// ----
	// *****************************************************************************************************************************************
    long breakString(const string &str, TokenDataListType &tdl, bool includeTokens = true);
    long breakString(const string &str, StringListType &sl, bool includeTokens = true);

}; // class TokenAnalisys

}; // namespace TEXTTOOLS;

#endif // ifndef __TOKENANALISYS
