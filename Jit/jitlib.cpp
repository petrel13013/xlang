#include "jitlib.h"
#include "compiler.h"
#include "cppcompiler.h"

namespace X
{
	namespace Jit
	{
		JitLib::~JitLib()
		{
			for (auto* pCompiler : m_compilers)
			{
				if (pCompiler != nullptr)
				{
					delete pCompiler;
				}
			}
		}
		std::string JitLib::QuotePath(std::string& strSrc)
		{
			std::string strNew = strSrc;
			ReplaceAll(strNew, "\\", "\\\\");
			strNew = "\"" + strNew + "\"";
			return strNew;
		}
		bool JitLib::Build()
		{
			for (auto& funcInfo : m_funcs)
			{
				switch (funcInfo.langType)
				{
				case LangType::cpp:
					if (m_compilers[(int)LangType::cpp] == nullptr)
					{
						auto* pCompiler = new CppCompiler();
						pCompiler->SetLib(this);
						std::string useDefault;
						pCompiler->Init(useDefault);
						m_compilers[(int)LangType::cpp] = pCompiler;
					}
					break;
				default:
					break;
				}
			}
			for (int i = 0; i < (int)LangType::Count; i++)
			{
				JitCompiler* pCompiler = m_compilers[i];
				if (pCompiler == nullptr)
				{
					continue;
				}
				std::vector<std::string> srcs;
				std::vector<std::string> exports;
				BuildCodeAction action;
				pCompiler->BuildCode(srcs,exports,action);
				if (action == BuildCodeAction::NeedBuild)
				{
					pCompiler->CompileAndLink(srcs);
					pCompiler->LoadLib();
				}
			}
			return true;
		}
	}
}

