#ifndef __VECTOR_RU__
#define __VECTOR_RU__

#include "meta.h"

#preproc_passes(1,"_.C")

#scan(vecProgram,vecScalar,vecVector,vecMat,vecInput,vecOut,vecTest,vecTerminator,metaCleanup,metaIntroduce,metaStop)

#def_xpath Mp1ii($i0,$i1) {
	(count(//Link[Name/text()="Mp" and Left/Value/text()=$i0 and Right/Value/text()=$i1]) > 0)
}

#def_xpath MVIv1ii($i0,$i1) {
	(count(//Link[Name/text()="MVIv" and Left/Value/text()=$i0 and Right/Value/text()=$i1]) > 0)
}

#def_xpath MVv1ii($i0,$i1) {
	(count(//Link[Name/text()="MVv" and Left/Value/text()=$i0 and Right/Value/text()=$i1]) > 0)
}

#def_xpath MVv1io($i0,&$o1) {
	(count(//Link[Name/text()="MVv" and Left/Value/text()=$i0 and set($o1,Right/Value/text())]) > 0)
}

#def_xpath MVv1oi(&$o0,$i1) {
	(count(//Link[Name/text()="MVv" and set($o0,Left/Value/text()) and Right/Value/text()=$i1]) > 0)
}

#def_xpath NXv0io($i0,&$o1) {
	(count(//Link[Name/text()="NXv" and Right/Value/text()=$i0 and set($o1,Left/Value/text())]) > 0)
}

#def_pattern vecProgram => vector_sentence(gid(), 'Program', '', '', '') {
  @begin
   \#\(
   ()->{V0}
   (([^\.]+\.)->{Grammar.ru{SENTENCE}})?=>{
      xpathf(SENTENCE,'MVv1oi',$V0,'программу','true'),(similar(V0,'Написать',2);similar(V0,'Составить',2))
   }(*PRUNE)
   \)\\n
  @end
};

#def_pattern vecScalar => vector_sentence(gid(), 'Scalar', '', '', //P0/@Value) {
  @begin
   \#\(
   ()->{V0}
   (([^\w\.]+(\w+)->{P0}[^\.]*\.)->{Grammar.ru{SENTENCE}})?=>{
      xpathf(SENTENCE,'MVv1oi',$V0,'скаляр','true'),(eq(V0,'ввести');eq(V0,'Ввести');similar(V0,'Определить',2))
   }(*PRUNE)
   \)\\n
  @end
};

#def_pattern vecVector => vector_sentence(gid(), 'Vector', '', //P1/@Value, //P0/@Value) {
  @begin
   \#\(
   (([^\w\.]+(\w+)->{P0}[^\w\.]+(\w+)->{P1}[^\.]*\.)->{Grammar.ru{SENTENCE}})?=>{
      (xpathf(SENTENCE,'MVv1ii','Введем','вектор','true');xpathf(SENTENCE,'MVv1ii','введем','вектор','true')),
      xpathf(SENTENCE,'Mp1ii','вектор','из','true')
   }(*PRUNE)
   \)\\n
  @end
};

#def_pattern vecMat => vector_sentence(gid(), 'Mat', //P0/@Value, //VRES0/@Value, //P1/@Value) {
  @begin
   \#\(
   ()->{V0}()->{V3}()->{VRES0}
   (([^\w\.]+(\w+)->{P0}[^\w\.]+(\w+)->{P1}[^\.]*\.)->{Grammar.ru{SENTENCE}})?=>{
      xpathf(SENTENCE,'MVv1oi',$V0,'результат','true'),
      (similar(V0,'Найдем',2);similar(V0,'Определим',2)),
      xpathf(SENTENCE,'NXv0io','результат',$V3,'true'),
      (similar(V3,'максимум',1),set($VRES0,'Max');
       similar(V3,'минимум',1),set($VRES0,'Min'))
   }(*PRUNE)
   \)\\n
  @end
};

#def_pattern vecInput => vector_sentence(gid(), 'Input', '', '', //P0/@Value) {
  @begin
   \#\(
   ()->{V0}
   (([^\w\.]+(\w+)->{P0}[^\.]*\.)->{Grammar.ru{SENTENCE}})?=>{
      xpathf(SENTENCE,'MVv1oi',$V0,'вектор','true'),(similar(V0,'Введем',2);similar(V0,'Зададим',2)),
      xpathf(SENTENCE,'Mp1ii','вектор','с','true')
   }(*PRUNE)
   \)\\n
  @end
};

#def_pattern vecOut => vector_sentence(gid(), 'Out', '', '', //P0/@Value) {
  @begin
   \#\(
   ()->{V1}
   (([^\w\.]+(\w+)->{P0}[^\.]*\.)->{Grammar.ru{SENTENCE}})?=>{
      (xpathf(SENTENCE,'MVv1io','Вывести',$V1,'true');xpathf(SENTENCE,'MVv1io','вывести',$V1,'true')),
      (similar(V1,'вектор',2);similar(V1,'скаляр',2))
   }(*PRUNE)
   \)\\n
  @end
};

#def_pattern vecTest => vector_sentence(gid(), 'Test', //P0/@Value, '', //P1/@Value) {
  @begin
    \#\(
    (([^\x22\x27\.]+[\x22\x27]([^\x22\x27]+)->{P0}[\x22\x27][^\x22\x27\.]+[\x22\x27]([^\x22\x27]+)->{P1}[\x22\x27][^\.]*\.)->{Grammar.ru{SENTENCE}})?=>{
      (xpathf(SENTENCE,'MVIv1ii','Тест','дает','true');xpathf(SENTENCE,'MVIv1ii','тест','дает','true'))
    }(*PRUNE)
    \)\\n
  @end
};

#def_pattern vecTerminator => vector_generate(gid()) {
  @begin
    ($)->{END}
  @end
};

#def_module() vector_sentence(GID, TYPE, OBJECT, OP, SUBJECT) {
@goal:-brackets_off.
@goal:-assertz(model_obj(GID, TYPE, OBJECT, OP, SUBJECT)).
};

#def_module() vector_generate(GID_) {
@goal:-brackets_off.
@create_vector_obj(_, 'Program', _, _, _).
@create_vector_obj(_, 'Scalar', _, _, SUBJECT):-
   add_object(SUBJECT,clsSimpleScalar,[], 'Введем скаляр').
@create_vector_obj(_, 'Vector', _, OP, SUBJECT):-
   add_object(SUBJECT,clsSimpleVector,[param('Size',OP)], 'Введем вектор').
@create_vector_obj(_, 'Input', _, _, SUBJECT):-
   atom_concat('in', SUBJECT, ID),
   add_object(ID,clsSimpleInput,[param('IVar',SUBJECT)], 'Введем вектор с клавиатуры').
@create_vector_obj(_, 'Mat', OBJECT, OP, SUBJECT):-
   atom_concat(OP, OBJECT, A1), atom_concat(A1, SUBJECT, ID),
   (=(OP, 'Max')->
     =(VERBALLY, 'максимум');
     =(VERBALLY, 'минимум')
   ),
   atom_concat('Найдем ', VERBALLY, SENT),
   add_object(ID,clsSimpleMat,[param('IVar',OBJECT),param('OVar',SUBJECT),param('Op',OP)], SENT).
@create_vector_obj(_, 'Out', _, _, SUBJECT):-
   atom_concat('out', SUBJECT, ID),
   add_object(ID,clsSimpleOut,[param('IVar',SUBJECT)], 'Вывести скаляр на экран').
@create_vector_obj(GID, 'Test', OBJECT, _, SUBJECT):-
   atom_concat('test', GID, ID),
		add_object(ID,clsSimpleTest,[param('Input',OBJECT),param('Output',SUBJECT)], '').
@goal:-
  load_classes('./Classes/clsSimpleProgs','object','link'),
  init_xpathing('RussianGrammar'),
  !,
  (
   model_obj(GID, TYPE, OBJECT, OP, SUBJECT), create_vector_obj(GID, TYPE, OBJECT, OP, SUBJECT), fail;
   true
  ),
  !,
  add_object('END',clsSimpleTerminator,[], ''),
  prepare_model_for_induct(A),
  induct_xpathing(60, 6, A, '_.xml', t, f, f),
  import_model_after_induct('_.xml'),
  prepare_model_for_induct('__prepared.xml'),
  unload_classes.
};

#endif
