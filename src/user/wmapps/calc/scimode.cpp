#define BTOS_NO_USING

#include "scimode.hpp"
#include <gui/button.hpp>
#include <dev/keyboard.h>

#include <util/tinyformat.hpp>

#include <queue>
#include <stack>
#include <cmath>

namespace gds = btos_api::gds;
namespace gui = btos_api::gui;

class EvalError : public std::exception {};

static double fact(double v){
	v = floor(v);
	if(v < 0.0) throw EvalError();
	if(v - 1.0 != v){
		double r = v;
		while(v > 1.0){
			v -= 1.0;
			r *= v;
		}
		return r;
	}else return INFINITY;
}

static bool toDouble(const std::string &str, double &v){
	char *ptr;
	v = strtod(str.c_str(), &ptr);
	if(v == 0.0 && (!ptr || *ptr != '\0')) return false;
	else return true;
}

ScientificMode::ScientificMode(const gds::Point &p) : pos(p) {}

std::function<void()> ScientificMode::MakeHandler(const std::string &str){
	return [&, str]{
		if(awaiting) HandleClear();
		auto v = output->GetValue();
		v += str;
		output->SetText(v);
	};
}

bool ScientificMode::HandleKeyPress(uint32_t key){
	if(awaiting) HandleClear();
	if(!(key & KeyFlags::NonASCII)){
		char c = KB_char(key);
		if(c == '=' || c == '\n'){
			Calculate();
			return true;
		}
	}else if(KB_code(key) == (KeyFlags::NonASCII | KeyCodes::Delete)){
		HandleClear();
		return true;
	}
	return false;
}

void ScientificMode::HandleClear(){
	output->SetText("");
	awaiting = false;
}

void ScientificMode::Calculate(){
	const std::vector<char> delims = {'*', '/', '^', '(', ')', '!'};
	const std::map<char, char> usuallyDelims = {{'+', 'E'}, {'-', 'E'}, {'r', 'q'}};
	
	auto exp = output->GetValue();
	std::vector<std::string> tokens;
	
	std::string ctok;
	for(auto c : exp){
		if(std::find(delims.begin(), delims.end(), c) != delims.end() || 
		(usuallyDelims.find(c) != usuallyDelims.end() && ctok.back() != usuallyDelims.at(c))){
			if(!ctok.empty()) tokens.push_back(ctok);
			ctok.clear();
			tokens.push_back(std::string(1, c));
		}else ctok += c;
	}
	if(!ctok.empty()) tokens.push_back(ctok);
	
	// tfm::printf("Tokens: ");
	// for(auto &t : tokens) tfm::printf("\"%s\" ", t);
	// tfm::printf("\n");
	
	try{
		double result = Evaluate(tokens.begin(), tokens.end());
		ans = result;
		output->SetText(tfm::format("%G", result));
	}catch(EvalError&){
		output->SetText("ERROR!");
	}
	awaiting = true;
}

double ScientificMode::Evaluate(std::vector<std::string>::iterator begin, std::vector<std::string>::iterator end){
	const std::vector<std::string> functions = {"log", "ln", "log2", "sin", "cos", "tan", "asin", "acos", "atan", "sqrt"};
	const std::vector<std::string> operators = {"^", "r", "*", "/", "-", "+", "!"};
	
	const std::map<std::string, double> constants = {
		{"e", M_E}, 
		{"pi", M_PI},
		{"ANS", ans}
		
	};
	
	struct Item{
		enum{
			Value, Op, Func
		} type = Value;
		double value = 0.0;
		char op = '\0';
		std::string func = "";
		
		Item(double v) : value(v) {}
		Item(char c) : type(Op), op(c) {}
		Item(const std::string &s) : type(Func), func(s) {}
	};
	
	std::vector<Item> items;
	for(auto i = begin; i != end; ++i){
		auto &t = *i;
		double v;
		if(toDouble(t, v)) items.push_back(v);
		else if(t == "("){
			auto si = ++i;
			int count = 1;
			for(;i != end; ++i){
				auto &t = *i;
				if(t == "(") ++count;
				if(t == ")") --count;
				if(count == 0) break;
			}
			if(si != end && i != end){
				items.push_back(Evaluate(si, i));
			}
			if(i == end) break;
		}else if(std::find(functions.begin(), functions.end(), t) != functions.end()){
			items.push_back(t);
		}else if(std::find(operators.begin(), operators.end(), t) != operators.end()){
			items.push_back(t[0]);
		}else if(constants.find(t) != constants.end()){
			items.push_back(constants.at(t));
		}else throw EvalError();
	}
	
	// tfm::printf("Items: ");
	// for(auto &i : items){
	// 	switch(i.type){
	// 		case Item::Value:
	// 			tfm::printf("{Value: %s} ", i.value);
	// 			break;
	// 		case Item::Op:
	// 			tfm::printf("{Op: %s} ", i.op);
	// 			break;
	// 		case Item::Func:
	// 			tfm::printf("{Func: %s} ", i.func);
	// 			break;
	// 	}
	// }
	// tfm::printf("\n");
	
	std::queue<Item> output;
	std::stack<char> opStack;
	
	std::string func = "";
	for(auto &i : items){
		switch(i.type){
			case Item::Value:{
				auto v = i.value;
				if(!func.empty()){
					v = EvalFunc(func, v);
					func.clear();
				}
				output.push(v);
				break;
			}
			case Item::Func:
				func = i.func;
				break;
			case Item::Op:
				if(!opStack.empty()){
					auto opStr = std::string(1, i.op);
					auto opStr2 = std::string(1, opStack.top());
					if(std::find(operators.begin(), operators.end(), opStr) > std::find(operators.begin(), operators.end(), opStr2)){
						while(!opStack.empty()){
							output.push(opStack.top());
							opStack.pop();
						}
					}
				}
				opStack.push(i.op);
				break;
		}
	}
	while(!opStack.empty()){
		output.push(opStack.top());
		opStack.pop();
	}
	
	// auto outputCopy = output;
	// tfm::printf("Output: ");
	// while(!outputCopy.empty()){
	// 	auto &i = outputCopy.front();
	// 	switch(i.type){
	// 		case Item::Value:
	// 			tfm::printf("{Value: %s} ", i.value);
	// 			break;
	// 		case Item::Op:
	// 			tfm::printf("{Op: %s} ", i.op);
	// 			break;
	// 		case Item::Func:
	// 			tfm::printf("{Func: %s} ", i.func);
	// 			break;
	// 	}
	// 	outputCopy.pop();
	// }
	// tfm::printf("\n");
	
	std::stack<double> evalStack;
	while(!output.empty()){
		auto &o = output.front();
		if(o.type == Item::Value) evalStack.push(o.value);
		else{
			if(o.op == '!'){
				if(evalStack.empty()) throw EvalError();
				auto v = evalStack.top();
				evalStack.pop();
				evalStack.push(fact(v));
			}else{
				if(evalStack.empty()) throw EvalError();
				double v1, v2, r;
				v1 = evalStack.top();
				evalStack.pop();
				if(!evalStack.empty()){
					v2 = evalStack.top();
					evalStack.pop();
				}else v2 = 0.0;
				switch(o.op){
					case '+':
						r = v2 + v1;
						break;
					case '-':
						r = v2 - v1;
						break;
					case '/':
						r = v2 / v1;
						break;
					case '*':
						r = v2 * v1;
						break;
					case '^':
						r = pow(v2, v1);
						break;
					case 'r':
						r = pow(v1, (1.0/v2));
						break;
				}
				evalStack.push(r);
			}
		}
		output.pop();
	}
	
	// auto evalStackCopy = evalStack;
	// tfm::printf("EvalStack: ");
	// while(!evalStackCopy.empty()){
	// 	tfm::printf("%s ", evalStackCopy.top());
	// 	evalStackCopy.pop();
	// }
	// tfm::printf("\n");
	
	if(!evalStack.empty()) return evalStack.top();
	else throw EvalError();
}

double ScientificMode::EvalFunc(const std::string &func, double param){
	if(func == "log") return log10(param);
	else if(func ==  "ln") return log(param);
	else if(func ==  "log2") return log2(param);
	else if(func == "sin") return sin(ConvertAngleIn(param));
	else if(func == "cos") return cos(ConvertAngleIn(param));
	else if(func == "tan") return tan(ConvertAngleIn(param));
	else if(func == "asin") return ConvertAngleOut(asin(param));
	else if(func == "acos") return ConvertAngleOut(acos(param));
	else if(func == "atan") return ConvertAngleOut(atan(param));
	else if(func == "sqrt") return sqrt(param);
	else throw EvalError();
}

double ScientificMode::ConvertAngleIn(double a){
	if(modeGroup.GetValue() == AngleMode::Degrees){
		return a * M_PI / 180.0;
	}else return a;
}

double ScientificMode::ConvertAngleOut(double a){
	if(modeGroup.GetValue() == AngleMode::Degrees){
		return a * 180.0 / M_PI;
	}else return a;
}

std::shared_ptr<gui::Form> ScientificMode::Show(){
	using namespace std::placeholders;
	
	auto form = std::make_shared<gui::Form>(gds::Rect{pos.x, pos.y, 510, 237}, gui::FormOptions::Fixed, "Calculator");
	MakeToolbarAndMenu(form);
	
	output = std::make_shared<gui::TextBox>(gds::Rect{10, 42, 380, 25});
	output->OnKeyPress(std::bind(&ScientificMode::HandleKeyPress, this, _1));
	
	auto opDivide = std::make_shared<gui::Button>(gds::Rect{170, 77, 30, 30}, "\xC3\xB7");
	opDivide->OnAction(MakeHandler("/"));
	auto opMultiply = std::make_shared<gui::Button>(gds::Rect{170, 117, 30, 30}, "\xC3\x97");
	opMultiply->OnAction(MakeHandler("*"));
	auto opSubtract = std::make_shared<gui::Button>(gds::Rect{170, 157, 30, 30}, "-");
	opSubtract->OnAction(MakeHandler("-"));
	auto opAdd = std::make_shared<gui::Button>(gds::Rect{170, 197, 30, 30}, "+");
	opAdd->OnAction(MakeHandler("+"));
	
	auto clear = std::make_shared<gui::Button>(gds::Rect{10, 77, 30, 30}, "C");
	clear->OnAction(std::bind(&ScientificMode::HandleClear, this));
	auto opAns = std::make_shared<gui::Button>(gds::Rect{10, 117, 30, 30}, "ANS");
	opAns->OnAction(MakeHandler("ANS"));
	auto opEquals = std::make_shared<gui::Button>(gds::Rect{10, 157, 30, 70}, "=");
	opEquals->OnAction(std::bind(&ScientificMode::Calculate, this));
	
	auto digit7 = std::make_shared<gui::Button>(gds::Rect{50, 77, 30, 30}, "7");
	digit7->OnAction(MakeHandler("7"));
	auto digit8 = std::make_shared<gui::Button>(gds::Rect{90, 77, 30, 30}, "8");
	digit8->OnAction(MakeHandler("8"));
	auto digit9 = std::make_shared<gui::Button>(gds::Rect{130, 77, 30, 30}, "9");
	digit9->OnAction(MakeHandler("9"));
	
	auto digit4 = std::make_shared<gui::Button>(gds::Rect{50, 117, 30, 30}, "4");
	digit4->OnAction(MakeHandler("4"));
	auto digit5 = std::make_shared<gui::Button>(gds::Rect{90, 117, 30, 30}, "5");
	digit5->OnAction(MakeHandler("5"));
	auto digit6 = std::make_shared<gui::Button>(gds::Rect{130, 117, 30, 30}, "6");
	digit6->OnAction(MakeHandler("6"));
	
	auto digit1 = std::make_shared<gui::Button>(gds::Rect{50, 157, 30, 30}, "1");
	digit1->OnAction(MakeHandler("1"));
	auto digit2 = std::make_shared<gui::Button>(gds::Rect{90, 157, 30, 30}, "2");
	digit2->OnAction(MakeHandler("2"));
	auto digit3 = std::make_shared<gui::Button>(gds::Rect{130, 157, 30, 30}, "3");
	digit3->OnAction(MakeHandler("3"));
	
	auto digit0 = std::make_shared<gui::Button>(gds::Rect{50, 197, 30, 30}, "0");
	digit0->OnAction(MakeHandler("0"));
	auto decimal = std::make_shared<gui::Button>(gds::Rect{90, 197, 30, 30}, ".");
	decimal->OnAction(MakeHandler("."));
	auto opExp = std::make_shared<gui::Button>(gds::Rect{130, 197, 30, 30}, "EXP");
	opExp->OnAction(MakeHandler("E"));
	
	auto opLog = std::make_shared<gui::Button>(gds::Rect{210, 77, 50, 30}, "log");
	opLog->OnAction(MakeHandler("log("));
	auto opLn = std::make_shared<gui::Button>(gds::Rect{270, 77, 50, 30}, "ln");
	opLn->OnAction(MakeHandler("ln("));
	auto opLog2 = std::make_shared<gui::Button>(gds::Rect{330, 77, 50, 30}, "log\xE2\x82\x82");
	opLog2->OnAction(MakeHandler("log2("));
	auto opE = std::make_shared<gui::Button>(gds::Rect{390, 77, 50, 30}, "e");
	opE->OnAction(MakeHandler("e"));
	auto opPower = std::make_shared<gui::Button>(gds::Rect{450, 77, 50, 30}, "x^");
	opPower->OnAction(MakeHandler("^"));
	
	auto opSin = std::make_shared<gui::Button>(gds::Rect{210, 117, 50, 30}, "sin");
	opSin->OnAction(MakeHandler("sin("));
	auto opCos = std::make_shared<gui::Button>(gds::Rect{270, 117, 50, 30}, "cos");
	opCos->OnAction(MakeHandler("cos("));
	auto opTan = std::make_shared<gui::Button>(gds::Rect{330, 117, 50, 30}, "tan");
	opTan->OnAction(MakeHandler("tan("));
	auto opPi = std::make_shared<gui::Button>(gds::Rect{390, 117, 50, 30}, "\xCF\x80");
	opPi->OnAction(MakeHandler("pi"));
	auto opFact = std::make_shared<gui::Button>(gds::Rect{450, 117, 50, 30}, "!");
	opFact->OnAction(MakeHandler("!"));
	
	auto opASin = std::make_shared<gui::Button>(gds::Rect{210, 157, 50, 30}, "asin");
	opASin->OnAction(MakeHandler("asin("));
	auto opACos = std::make_shared<gui::Button>(gds::Rect{270, 157, 50, 30}, "acos");
	opACos->OnAction(MakeHandler("acos("));
	auto opATan = std::make_shared<gui::Button>(gds::Rect{330, 157, 50, 30}, "atan");
	opATan->OnAction(MakeHandler("atan("));
	auto opInv = std::make_shared<gui::Button>(gds::Rect{390, 157, 50, 30}, "\xC2\xB9\xE2\x81\x84x");
	opInv->OnAction(MakeHandler("1/"));
	auto opNeg = std::make_shared<gui::Button>(gds::Rect{450, 157, 50, 30}, "\xC2\xB1");
	opNeg->OnAction(MakeHandler("(-1)*"));
	
	auto opOpenParen = std::make_shared<gui::Button>(gds::Rect{210, 197, 50, 30}, "(");
	opOpenParen->OnAction(MakeHandler("("));
	auto opCloseParen = std::make_shared<gui::Button>(gds::Rect{270, 197, 50, 30}, ")");
	opCloseParen->OnAction(MakeHandler(")"));
	auto opSqrt = std::make_shared<gui::Button>(gds::Rect{330, 197, 50, 30}, "\xE2\x88\x9A");
	opSqrt->OnAction(MakeHandler("sqrt("));
	auto opNRoot = std::make_shared<gui::Button>(gds::Rect{390, 197, 50, 30}, "n\xE2\x88\x9A");
	opNRoot->OnAction(MakeHandler("r"));
	auto opSquared = std::make_shared<gui::Button>(gds::Rect{450, 197, 50, 30}, "x\xC2\xB2");
	opSquared->OnAction(MakeHandler("^2"));
	
	auto modeDeg = std::make_shared<gui::RadioButton>(gds::Rect{455, 40, 42, 25}, "DEG", true);
	auto modeRad = std::make_shared<gui::RadioButton>(gds::Rect{400, 40, 42, 25}, "RAD", false);
	modeGroup.AddButton(modeDeg, AngleMode::Degrees);
	modeGroup.AddButton(modeRad, AngleMode::Radians);
	
	form->AddControls({
		output, modeDeg, modeRad,
		opDivide, opMultiply, opSubtract, opAdd,
		clear, opAns, opEquals,
		digit7, digit8, digit9,
		digit4, digit5, digit6,
		digit1, digit2, digit3,
		digit0, decimal, opExp,
		opLog, opLn, opLog2, opE, opPower,
		opSin, opCos, opTan, opPi, opFact,
		opASin, opACos, opATan, opInv, opNeg,
		opOpenParen, opCloseParen, opSqrt, opNRoot, opSquared
	});
	form->SetFocus(output);
	return form;
}

std::string ScientificMode::GetValue(){
	return output->GetValue();
}

void ScientificMode::SetValue(const std::string &s){
	output->SetText(s);
}