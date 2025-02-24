#pragma once

#include "object.h"

namespace X
{
	namespace Data
	{
		class TypeObject :
			virtual public Object
		{
			std::string m_desc;
			ValueType m_valType = ValueType::Invalid;
			ObjType m_objType = ObjType::Base;

			X::Value m_realObj;

			virtual void GetBaseScopes(std::vector<AST::Scope*>& bases) override;
		public:
			static void Init();
			static void cleanup();

			TypeObject() :Object()
			{
				m_t = ObjType::Type;
			}
			TypeObject(Value& val) :TypeObject()
			{
				m_valType = val.GetType();
				if (m_valType == ValueType::Object)
				{
					m_objType = val.GetObj()->GetType();
				}
				m_realObj = val;
			}
			virtual const char* ToString(bool WithFormat = false) override
			{
				std::string strType;
				switch (m_valType)
				{
				case X::ValueType::Invalid:
					strType = "<class 'Invalid'>";
					break;
				case X::ValueType::None:
					strType = "<class 'NoneType'>";
					break;
				case X::ValueType::Int64:
					strType = "<class 'int'>";
					break;
				case X::ValueType::Double:
					strType = "<class 'float'>";
					break;
				case X::ValueType::Object:
				{
					switch (m_objType)
					{
					case X::ObjType::Base:
						strType = "<class 'object'>";
						break;
					case X::ObjType::Type:
						strType = "<class 'type'>";
						break;
					case X::ObjType::Str:
						strType = "<class 'str'>";
						break;
					case X::ObjType::Binary:
						strType = "<class 'bytes'>";
						break;
					case X::ObjType::Expr:
						strType = "<class 'expression'>";
						break;
					case X::ObjType::ConstExpr:
						strType = "<class 'const expression'>";
						break;
					case X::ObjType::Function:
						strType = "<class 'function'>";
						break;
					case X::ObjType::MetaFunction:
						strType = "<class 'metafunction'>";
						break;
					case X::ObjType::XClassObject:
						strType = "<class 'class'>";
						break;
					case X::ObjType::Prop:
						strType = "<class 'prop'>";
						break;
					case X::ObjType::ObjectEvent:
						strType = "<class 'event'>";
						break;
					case X::ObjType::FuncCalls:
						strType = "<class 'calls'>";
						break;
					case X::ObjType::Package:
						strType = "<class 'package'>";
						break;
					case X::ObjType::ModuleObject:
						strType = "<class 'module'>";
						break;
					case X::ObjType::Future:
						strType = "<class 'future'>";
						break;
					case X::ObjType::Iterator:
						strType = "<class 'iterator'>";
						break;
					case X::ObjType::List:
						strType = "<class 'list'>";
						break;
					case X::ObjType::Dict:
						strType = "<class 'dict'>";
						break;
					case X::ObjType::Set:
						strType = "<class 'set'>";
						break;
					case X::ObjType::Complex:
						strType = "<class 'complex'>";
						break;
					case X::ObjType::TableRow:
						strType = "<class 'tablerow'>";
						break;
					case X::ObjType::Table:
						strType = "<class 'table'>";
						break;
					case X::ObjType::RemoteObject:
						strType = "<class 'remoteobject'>";
						break;
					case X::ObjType::RemoteClientObject:
						strType = "<class 'remoteclientobject'>";
						break;
					case X::ObjType::PyProxyObject:
						strType = "<class 'pythonobject'>";
						break;
					default:
						break;
					}
				}
				break;
				case X::ValueType::Str:
					strType = "<class 'const str'>";
					break;
				case X::ValueType::Value:
					break;
				default:
					break;
				}
				return GetABIString(strType);
			}

			X::Value GetMembers(X::XlangRuntime* rt);
		};
	}
}