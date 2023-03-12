#include <iostream>

#scan(WhileElse)

#def_pattern WhileElse => while_else (gid(), /root/COND/@Value, /root/BODY/@Value) {
  (((^)|(\;)+|\}|\{|\)|\\n|(\\n|\\t|\b)else\b|(\\n|\\t|\b)do\b|\:)((\s|\\t)*\\n)*)(\s|\\t)*
  @begin
    (\s|\\t)*
    (while(\\n|\s|\\t)*\(
           (\\n|\s|\\t)*((.{1,300}?)->{COND}\))?=>{Predicates.BAL($,')')}
        )
    (\s|\\t)*
    \{
    (\\n|\s|\\t)*((.{1,8192}?)->{BODY}\})?=>{Predicates.BAL($,'}')}
    (\\n|\s|\\t)*
    else
  @end
  (\\n|\s|\\t)+
};

#def_module() while_else(GID, COND, BODY) {
@goal:-brackets_off.
@goal:-
  write('bool __break'), write(GID), write(' = false;'), nl,
  write('while('), write(COND), write(') {'), nl,
  write('  __break'), write(GID), write(' = true;'), nl,
  write(BODY), nl,
  write('  __break'), write(GID), write(' = false;'), nl,
  write('}'), nl,
  write('if (__break'), write(GID), write(') '), nl.
};

int main() {
	int A[10];
	int k = 0;

	while (k < 10) {
		cin >> A[k];
		if (A[k] == 0) break;
		k++;
	}
	else
		cout << "Был введен ноль!" << endl;

	return 0;
}