#include "TokenAnalisys.h"

namespace TEXTTOOLS
{

TokenIdentType
	lastIdentToken = -1;

/*
 * TokenAnalisys.
 * ------------------------------------------------------------------------------------------------------------------------------------------------
 */

TokenConfigStruct
TokenAnalysis::getTokenConfig(const string &token)
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

void
TokenAnalysis::setTokenConfig(const string &token, TokenConfigStruct config)
{
MapTokenDataType::iterator	
	dit = m_mtiTokens.find(token);

	if (dit == m_mtiTokens.end())
		RAISE(ETokenAnalisys, ERR_INVALID_TOKEN);

MapTokenConfigType::iterator
	it = m_mtcTokensConfig.find(dit->second.ident);

	it->second = config;
};

bool
TokenAnalysis::tokenConfigByIdent(TokenIdentType ident, TokenConfigStruct *config)
{
MapTokenConfigType::iterator
	it = m_mtcTokensConfig.find(ident);
bool
	blnResult = it != m_mtcTokensConfig.end();

	if (blnResult && config)
		*config = it->second;

	return blnResult;
};

void
TokenAnalysis::addToken(TokenIdentType ident, const string &token, TokenConfigStruct config)
{
    if (m_mtiTokens.find(token) != m_mtiTokens.end())
        RAISE(ETokenAnalisys, ERR_DUPLICATE_TOKEN);

	if (m_taConfig.uniqueTokenId && tokenConfigByIdent(ident))
		RAISE(ETokenAnalisys, ERR_DUPLICATE_IDENT);

TokenDataStruct
	td;

	td.ident = ident;
	td.str = token;

    m_mtiTokens.insert( pair<string, TokenDataStruct>(token, td) );
	m_mtcTokensConfig.insert( pair<TokenIdentType, TokenConfigStruct>(ident, config));
};

long
TokenAnalysis::breakString(const string &str, TokenDataListType &tdl, bool includeTokens)
{
MapTokenDataType::reverse_iterator
	rit;
unsigned long
	lngLastPos = 0,
	lngPos = 0;
string
	strSubStr;
TokenDataStruct
	tdAppellant = TOKEN_DATA_NULL;

    while (lngPos < str.length())
    {

        rit = m_mtiTokens.rbegin();
        while (rit != m_mtiTokens.rend())
        {
        string strToken = rit->first;

            strSubStr = str.substr(lngPos, strToken.length());

            if (strSubStr == strToken)
            {
            TokenConfigStruct td = getTokenConfig(strToken);
            TokenDataStruct tknData;

                if (lngPos - lngLastPos > 0)
                {
                    tknData.str = str.substr(lngLastPos, lngPos - lngLastPos);
                    tknData.ident = TOKEN_IDENT_NULL;

                    tdl.push_back(tknData);
                };

				lngPos += strToken.length();
				lngLastPos = lngPos;
				
				if (!td.ignore)
				{
					// Caso o token tenha configuração para ser recorrente, a pesquisa não será reiniciada nem o token reconhecido será inserido 
					// ---- na lista de resultados. Com isso, ele será testado novamente até que não haja mais um reconhecimento positivo. Então,
					//		a porçcão que foi anteriormente reconhecida será adicionada a lista.
					if (!td.appellant)
					{
						if (!td.ignore && includeTokens)
					    {
						    tknData.str = strToken;
							tknData.ident = rit->second.ident;

						    tdl.push_back(tknData);
		                };

			            rit = m_mtiTokens.rbegin();
					}
					else
					{
						tdAppellant.str += strToken;
						tdAppellant.ident = rit->second.ident;
					};
				}
            }
            else
			{
				if (tdAppellant.str.size())
				{
					tdl.push_back(tdAppellant);
					tdAppellant = TOKEN_DATA_NULL;
				};

                rit++;
			};
        };

        lngPos++;
    };

    strSubStr = str.substr(lngLastPos, lngPos - lngLastPos);

    if (strSubStr.length())
    {
    TokenDataStruct tknData;

        tknData.str = strSubStr;
		tknData.ident = TOKEN_IDENT_NULL;

        tdl.push_back(tknData);
    };

    return tdl.size();
};

long
TokenAnalysis::breakString(const string &str, StringListType &sl, bool includeTokens)
{
TokenDataListType tdl;
long lngResult;

    lngResult = breakString(str, tdl, includeTokens);

    for (TokenDataListType::iterator it = tdl.begin(); it != tdl.end(); it++)
        sl.push_back(it->str);

    return lngResult;
};

}; // namespace TEXTTOOLS;
