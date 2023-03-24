#define _CRT_SECURE_NO_WARNINGS

#pragma comment(linker, "/STACK:96000000")

#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <string.h>

#define ANTLR4CPP_STATIC

#include "antlr4-runtime.h"
#include "ReentLexer.h"
#include "ReentParser.h"

#ifdef __linux__
#include <sys/resource.h>
#endif

#pragma execution_character_set("utf-8")

using namespace antlr4;

ReentLexer * lexer = NULL;
ReentParser * parser = NULL;

class ErrorReporter : public DefaultErrorStrategy {
   virtual void reportFailedPredicate(Parser *recognizer, const FailedPredicateException &e) {
     recognizer->notifyErrorListeners(e.getOffendingToken(), const_cast<FailedPredicateException *>(&e)->getPredicate(), std::make_exception_ptr(e));
   }
};

class ErrorListener : public BaseErrorListener {
public:
  static ErrorListener INSTANCE;

  virtual void syntaxError(Recognizer * recognizer, Token * /*offendingSymbol*/,
		size_t line, size_t charPositionInLine, const std::string &msg, std::exception_ptr /*e*/) override {
	  if (lexer->__lines.size()) {
		  int nl = line;
		  while (nl && lexer->__lines.find(nl) == lexer->__lines.end()) nl--;
		  if (nl == 0)
			  std::cout << "Error: " << msg << " in line " << line << ":" << charPositionInLine << std::endl;
		  else {
			  std::string dest = lexer->__lines[nl];
			  char file[512];
			  sscanf(dest.c_str(), "#line %i \"%[^\"]\"", &line, file);
			  std::cout << "Error: " << msg << " in line " << line << ":" << charPositionInLine <<
				  " [" << file << "]" << std::endl;
		  }
	  }
	  else
		  std::cout << "line " << line << ":" << charPositionInLine << " " << msg << std::endl;
  }
};

ErrorListener ErrorListener::INSTANCE;

bool utf8_check_is_valid(const std::string& str)
{
    int c,i,ix,n,j;
    for (i=0, ix=str.length(); i < ix; i++)
    {
        c = (unsigned char) str[i];
        if (0x00 <= c && c <= 0x7f) n=0; // 0bbbbbbb
        else if ((c & 0xE0) == 0xC0) n=1; // 110bbbbb
        else if ( c==0xed && i<(ix-1) && ((unsigned char)str[i+1] & 0xa0)==0xa0) return false; //U+d800 to U+dfff
        else if ((c & 0xF0) == 0xE0) n=2; // 1110bbbb
        else if ((c & 0xF8) == 0xF0) n=3; // 11110bbb
        //else if (($c & 0xFC) == 0xF8) n=4; // 111110bb //byte 5, unnecessary in 4 byte UTF-8
        //else if (($c & 0xFE) == 0xFC) n=5; // 1111110b //byte 6, unnecessary in 4 byte UTF-8
        else return false;
        for (j=0; j<n && i<ix; j++) { // n bytes matching 10bbbbbb follow ?
            if ((++i == ix) || (( (unsigned char)str[i] & 0xC0) != 0x80))
                return false;
        }
    }
    return true;
}

int main(int argc, const char * argv[]) {
  if (argc < 2) {
	std::cout << "lexer_plc.exe <file.cpp> [output_tree]" << std::endl;
	return 1;
  }
#ifdef __linux__
  struct rlimit rl = { RLIM_INFINITY, RLIM_INFINITY };
  int result = setrlimit(RLIMIT_STACK, &rl);
  if (result != 0) {
     std::cout << "setrlimit returned result = " << result << std::endl;
     exit(1000);
  }
#endif
  std::ifstream in(argv[1]);
  if (in) {
     std::string prog;
     std::string line;
     while (std::getline(in, line))
        prog += line + "\n";
     in.close();
     if (utf8_check_is_valid(prog)) {
        ANTLRInputStream input(prog);
        lexer = new ReentLexer(&input);
		lexer->removeErrorListeners();
        lexer->addErrorListener(&ErrorListener::INSTANCE);
        CommonTokenStream tokens(lexer);

        parser = new ReentParser(&tokens);
        parser->getInterpreter<atn::ParserATNSimulator>()->setPredictionMode(atn::PredictionMode::SLL);
		parser->removeErrorListeners();
		parser->addErrorListener(&ErrorListener::INSTANCE);
		parser->setErrorHandler(std::make_shared<ErrorReporter>());
        tree::ParseTree *tree = parser->translationUnit();

		if (argc > 2 && strcmp(argv[2], "output_tree") == 0) {
			std::wstring s = antlrcpp::s2ws(tree->toStringTree(parser)) + L"\n";
			std::wcout << s;
	  }
     } else
        std::cout << "Non-UTF8 encoding!" << std::endl;
  }

  return 0;
}
