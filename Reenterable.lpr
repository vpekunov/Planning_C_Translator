// Важная информация для разработчиков. В ПППВ на конвейере ряд важных параметров
// передается в виде битовых масок:
// int __nprocs__ = {iiiiiiii iiiiiiig ftttttnn nnnnnnnn}.
//   i - бит индекса ПППВ в топологии (1..2^15-1)
//   f - флаговый бит -- запущена ли ПППВ на топологии/конвейере в одномашинном варианте
//   g - флаговый бит -- запущена ли ПППВ на топологии/конвейере в многомашинном варианте
//   t - бит номера топологии (0..2^5-1)
//   n - бит числа процессоров (0..1023)
// char __parallelize__ = {00000itp}.
//   i - имеют ли все ПППВ топологии/конвейера инициализационную стадию и, соответственно,
//       будут ли они вместе выполнять барьер. Для топологии всегда = 1. В последовательном
//       режиме всегда = 0.
//   t - топология(1) или простой конвейер(0). Определяет, в-основном, тип выхода --
//       автоматический для простого конвейера или по plan_topology_quit() для топологии.
//   p - параллельный ли режим.

{ 06.12.2021 Release V0.94beta3 (Planning C)                                     }
{ + Разработана первая версия объектно-транзакционного параллельного расширения, }
{   позволяющего динамически порождать параллельные soft-транзакционные страницы,}
{   что, в перспективе, должно привести к идеологии по типу object-transaction }
{   Cilk. Написан пример: решение задачи целочисленной нелинейной оптимизации. }
{ + Добавлена возможность менять механизм согласования транзакционных скаляров }
{   TScalar, навешивая на них функциональные обработчики типа A=f(A,B), что,   }
{   например, позволяет реализовать редукционные схемы, когда при согласовании }
{   скаляр не определяет победителя, а "сливает" частные результаты отдельных  }
{   страниц в конечное значение. Написан соответствующий пример: обучение      }
{   искусственной нейронной сети с редукцией по суммированию при определении   }
{   дельт.                                                                     }

{ 18.09.2021 Release V0.94beta2 (Planning C)                                   }
{ + Теперь появились сканирующие макросы, которые представляют регулярное      }
{   выражение с пре- и постконтекстом. Сканирующие макросы выполняются         }
{   перед "старой" второй фазой препроцессинга -- заменяют найденные выражения }
{   на указанные обращения к дедуктивным макромодулям или вставляют указанный  }
{   факт в БФ Пролога. Могут работать в режиме жесткого парсинга всего текста  }
{   программы или свободного сканирования.                                     }
{ + На базе сканирующих макросов и дедуктивных макромодулей построены расширения: }
{   * Автоматический распараллеливатель с применением Cilk (cilk_compile.h)    }
{   * Автоматический распараллеливатель с применением сверхоптимистичных       }
{     вычислений (atomic_compile.h).                                           }
{   * Анонимные процедуры и функции с повторным входом, анонимные вектора и    }
{     цепи, анонимные топологии общего вида. Библиотека reentera.h             }
{   * Стандартные топологии clique, star, ring, tube, pyramide и т.п.          }
{     Библиотека stdtopo.h                                                     }
{   * Виртуальный Power XPlorer контейнер, позволяющий создавать и отлаживать  }
{     простые C++ программы в стиле Parsytec Power XPlorer. Библиотека sun.h   }
{   * Простая и интерп/экстрап (МГУА, нейросети feed-forward, лин. экстрапол.) }
{     мемоизация аргументов. Директива                                         }
{     #pragma memoize [(feed_forward(...)|lin_extrapolator(...)|               }
{                       mgua(точность)) [controlled(...)|conditions(...)]]     }
{     Библиотека memoization.h                                                 }
{ + На базе нейросетевой и МГУА - мемоизаций, фактически, в язык вводятся      }
{   соответствующие интерполяторы, обучаемые простыми вызовами мемоизируемой   }
{   процедуры не в режимах controlled/conditions, а вызов предиктора           }
{   обеспечивается префиксом predict_ к мемоизованной процедуре/функции.       }
{ + Параметр командной строки -extensionsonly ВЫКЛЮЧАЕТ помещение в код        }
{   специфической преамбулы и функций Planning C, что может быть полезно, если }
{   транслятор используется исключительно для реализации новых расщирений C++. }

{ 20.03.2021 Release V0.94beta (Planning C)                                    }
{ + Теперь дедуктивные макромодули могут работать в режиме согласования        }
{   друг с другом -- достаточно пополнить базу фактов GNU PROLOG и задать      }
{   более одного выполнения полного препроцессинга. Факты при этом будут       }
{   "выживать" между препроцессингами, позволяя на более поздних стадиях       }
{   реагировать на пополнения БФ прочими дедуктивными макромодулями на         }
{   предыдущих стадиях. Число препроцессингов N задается #preproc_stages(N)    }
{   Принудительно завершить цикл препроцессингов можно, вызвав в макромодуле   }
{   специальный предикат prune.                                                }

{ 23.05.2020 Release V0.932beta (Planning C)                                   }
{ - Minor bug fixed                                                            }
{ + Введен новый режим исполнения групп этапов плана -- в частично             }
{   транзакционной программной памяти -- plan_group_soft_atomize               }
{   Соответственно, введены типы soft_transact_{var,array,in,out} для          }
{   программно-транзакционных скаляров, массивов и каналов. Каналы полностью   }
{   согласованы с частично транзакционной памятью, работает режим              }
{   сверхоптимистичных вычислений.                                             }

{ 06.08.2019 Release V0.931beta2 (Planning C)                                  }
{ - A lot of bugs fixed                                                        }
{ + Каналы с предикцией                                                        }

{ 16.09.2016 Release V0.931beta (Planning C)                                   }
{ - Some bugs fixed.                                                           }
{ + Препроцессор теперь обрабатывает подключения сторонних файлов, написанных  }
{   на Planning C. Обрабатываются только личные подключения: #include "файл"   }
{ + Введены новые функции plan_get_first, plan_get_last. Теперь можно извлекать}
{   значения из плана, не дожидаясь окончания этапа (за отсутствие чего автора }
{   много ругали).                                                             }
{ + Введено обращение по символическому имени при инициализации и получении    }
{   по запросу второго конца туннеля.                                          }
{ + Введена возможность запуска конвейера/топологии/вектора на кластере. Нужна }
{   #pragma plan clustered и префикс clustered(массив_MPI-идентификаторов).    }
{   В таком случае задействуются возможности MPI, программу компилируют с его  }
{   поддержечкой.                                                              }
{ + Реализованны туннели для связи процедур, запущенных в векторе/топологии/   }
{   конвейере на кластере. Это cfunnel вместо funnel, поддерживающий взаимо-   }
{   подключение ТОЛЬКО ПО УНИКАЛЬНОМУ ОБЩЕМУ ИМЕНИ.                            }
{ + Прочие доработки. В том числе добавление процесса в группу plan_register.  }
{ + Глобальные семафоры и обычные глобальные переменные при работе на кластере }
{ + Введена возможность исполнения плана/группы плана процедуры на расширителе,}
{   поддерживающем OpenCL: SSE-процессоре, многоядерной видеокарте. Нужна      }
{   #pragma plan vectorized, адекватная разметка параметров-указателей проце-  }
{   дуры аттрибутами _local(P) и _global(P), где P -- число элементов, зака-   }
{   чиваемых с указателя в расширитель на конкретном этапе исполнения, и       }
{   уверенное применение директивы параллелизации plan_group_vectorize(S).     }
{ * Сняты некоторые ограничения, не свойственные свободному синтаксису C++,    }
{   в частности, теперь многие конструкции Planning C можно писать в произволь-}
{   ное количество строк.                                                      }
{ * Для поддержки кластера нужен установленный MPI, для поддержки векторных    }
{   расширителей нужен OpenCL. В обоих случаях дополнительно НЕОБХОДИМ OpenMP. }
{ * Проект реструктурирован: выделены модули, оформлены нсколько процедур.     }

{ 30.08.2016 Release V0.92beta (Planning C)                                    }
{ * Проект сменил имя на Planning C.                                           }
{ * Автор выражает благодарность А.Е.Акимову-Тимьянову за позволение расширить }
{ прежний проект этой новой веткой и вести ее разработку самостоятельно.       }
{ + Добавлен ряд новых функций в каналы (funnels).                             }
{ - Исправлен ряд мелких просчетов при помещении в цепь процедуры без парамет- }
{   ров. Исправлены прочие мелкие недочеты (с однострочными комментариями).    }
{ - Исправлены мелкие огрехи, вызывавшие иногда зависание конвейеров.          }
{ + Разработаны виртуальные топологии (plan_topology), на основе которых       }
{ в языке появились дедуктивные макромодули (более общий случай блоков,        }
{ первоначально описывающих виртуальные топологии).                            }
{ * Исправлены различные мелкие ошибки.                                        }

{ 07.06.2016 Release V0.4beta                                                  }
{ + Начаты работы по реализации задумок по замене массивов и списков C++       }
{ планами. Такие планы генерируются СТАТИЧЕСКИМИ процедурами. Для таких        }
{ процедур определены макросы plan_type(procname), plan_item_type(procname).   }
{ Для получения плана процедуры определена операция *procname. Для работы с    }
{ планом теперь есть операторы >>,<<,++plan,plan++, макрос _size(plan).        }
{ + Теперь возможны и функции с планированием повторного входа. Они возвращают }
{ значение из последнего выполненного этапа плана. Есть ограничения: функции   }
{ не должны использовать статический план любого вида и не могут быть          }
{ элементами цепей (то есть chain -- ТОЛЬКО процедуры).                        }
{ + Начаты работы по созданию нового языка Planning C на базе ПППВ. Теперь     }
{ plan_first, plan_last, plan_stop и еще некоторые процедуры стали функциями,  }
{ возвращающими истину. За счет этого появилась возможность заменить циклы и   }
{ ветвления работой с процедурами.                                             }

{ 16.03.2016 Release V0.391beta                                                }
{ * Исправлена ошибка, из-за которой процедуры иногда зависали                 }
{ + Несколько модифицирован код для параллельного исполнения плана. Возможно,  }
{ что несколько повысится производительность                                   }

{ 14.03.2016 Release V0.39beta.                                                }
{ + Начата работа по реализации транзакционных блоков плана, синхронизирующихся}
{ через транзакционную память. Вводится директива plan_atomize для исполнения  }
{ блоков в транзакционном режиме (по аналогии с plan_parallelize).             }
{ Ограничения для такого исполнения:                                           }
{ 1. В цепях plan_atomize приводит к игнорированию попыток передать далее по   }
{ конвееру данные. Когда закончится транзакционная группа, все снова заработает}
{ 2. В транзакционных блоках ИГНОРИРУЮТСЯ все попытки изменения плана          }
{ 3. Указание числа ядер при вызове процедур через /N внутри блока игнорируется}
{ 4. Попытки вызвать continue <процедура> -- результаты непредсказуемы, видимо }
{ рекурсия.                                                                    }
{ 5. Не работает редукция, не работают декларированные зависимости по данным   }
{ 6. Работать пока будет только в GCC >= 4.7                                   }

// 15.10.2014. Авторские и имущественные права на программный код
// переданы А.Е.Акимову-Тимьянову для развития его научно-
// исследовательской работы.
// Дальнейшие версии неидентифицируются и не подлежат распространению
// иначе как с согласия правопреемников В.В.Пекунова, оставляюего за собой
// право на модернизацию кода в лично научных и иных некоммерческих целях,
// и правообладателя.

{ 19.02.2011 Release V0.382beta.                                               }
{ * Упрощен синтаксис разметки типов данных. Атрибут pre_id теперь не требует  }
{ указания значения пустой ссылки. Достаточно такого указания в id(...).       }

{ 14.02.2011 Release V0.381beta. Версия Дня святого Валентина ;)               }
{ * Исправлена ошибка: тоннель мог уничтожаться дважды, при вызове деструкто-  }
{ ров для объектов - двух его концов.                                          }
{ * Исправлена ошибка с разметкой рекурсивных типов. Проблема касалась хвосто- }
{ вых имен для внутренних рекурсивных ссылок.                                  }

{ 16.10.2009 Release V0.38beta                                                 }
{ + Автоматизирована проверка зависимостей по данным в рекурсивных структурах. }
{ Можно указать поля, хранящие ссылки на элементы-предпосылки расчета, поле-   }
{ флаг завершения обработки элемента и прочую информацию. Проверка реализована }
{ для параллельного варианта. Два варианта: модификаторы в заголовок процедуры }
{ и директивы разметки в определении типа. Также директива переопределения     }
{ разметки.                                                                    }
{ + Разметка работает как для стандартных имен типов структур, так и для       }
{ хвостовых имен.                                                              }

{ 20.08.2009 Release V0.372beta                                                }
{ * Исправлена редкая ошибка: в строке с указанием нескольких процедур с       }
{ повторным входом вторая и дальнейшие процедуры не распознавались как         }
{ таковые, если были декларированы до первой                                   }

{ 19.07.2009 Release V0.371beta                                                }
{ + Реализовал clear_plan, о котором, вообще говоря, уже давно забыл.          }
{   Эта директива требуется не так часто, но в волновом алгоритме поиска пути, }
{   реализацией которого занимался, несомненно необходима.                     }

{ 15.07.2009 Release V0.37beta                                                }
{ + Введена редукция для параметров процедур с повторным входом, как в        }
{   обычном так и в многопроцессорном режимах, в том числе для цепей.         }
{   Возможна редукция по любой коммутативной операции или бинарной функции.   }
{   Это выгодно отличает данную реализацию от OpenMP, где есть ограничения.   }
{   Кроме того, редукция не требует дополнительных усилий по ее               }
{   программированию, т.е. порождает весь необходимые код, а не является      }
{   лишь поправкой на параллелизм исполнения, как это реализовано в OpenMP    }

{ 12.01.2009 Release V0.36beta                                                }
{ + Реализован план с ограничением на размер reenterable[N]/chain[N]. Теперь  }
{   временные затраты на выделение памяти можно свести к минимуму.            }
{ * Оптимизирована схема блокировок при реализации конвеера                   }
{ + Чтобы уменьшить нагрузку на процессор и ОС, дать благоприятные условия    }
{   для параллельного исполнения других потоков во время циклов ожидания --   }
{   реализовал схему с сигналами/условными переменными (в зависимости от      }
{   возможностей ОС). Прирост производительности есть.                        }
{ + Теперь можно указывать количество процессоров для процедуры с повторным   }
{   входом, в том числе для произвольной стадии конвеера -- Proc(...)/N       }

{ 24.12.2008 Release V0.35beta                                                }
{  + Первые замеры эффективности параллельной версии на 2-ядерном (Core Duo)  }
{  компьютере в Windows. После проведенной оптимизации -- хорошие показатели  }
{  ! Автор выражает благодарность С.В.Пекунову за отладку и диагностировку    }
{  ошибок параллельной версии в среде MSVC 2008/Windows                       }
{  + Замеры эффективности параллельной версии на 2-ядерном (Core Duo)         }
{  компьютере в Fedora 9 Linux (GCC 4.1.2+ OpenMP). Результаты неожиданные.   }
{  MSVC 2005/2008 лучше оптимизирует код (GCC удивил пренебрежением к         }
{  инструкциям вида mov reg,[reg1+N*reg2], которые позволяют резко ускорить   }
{  расчет), зато GCC похоже более качественно реализует многопоточную обработ-}
{  ку в рамках стандарта OpenMP -- дал лучшие результаты по загрузке процесс- }
{  сора. Хотя не исключено, что это во многом эффект большей доли вычислитель-}
{  ной работы по сравнением с долей времени на организацию многопоточности.   }
{  Однако в одном из экспериментов (сортировка слиянием) это маловероятно,    }
{  следовательно, GCC/Linux реализует возможности OpenMP более качественно,   }
{  нежели MSVC/Windows.                                                       }
{  + Замеры эффективности параллельной версии на 4-ядерном (2*Opteron)        }
{  компьютере в SLAMD64 Linux (Intel Compiler 10.0.023 + OpenMP)              }
{  * После отладки на двухъядерном компьютере вставлена серия yield'ов,       }
{  чтобы не загружать процессор в циклах ожидания.                            }
{  * Туннели (funnel) -- вернулся к простой версии, которая в совокупности    }
{  с yield'ами оказалась не хуже предыдущей. Обнаружил, что                   }
{  последовательность unset_lock(A)+set_lock(A) иногда может выполниться,     }
{  "не обращая" внимания на set_lock(A), который уже был затребован другим    }
{  процессом. Понятно почему (операционная система не дала квант второму      }
{  процессору), но очень нелогично со стороны системы не следить за           }
{  корректностью таких блокировок. Неясно, чья проблема -- OpenMP (MSVC)      }
{  или Windows                                                                }

{ 12.2008 Release V0.34beta                                                   }
{  + Последняя версия, отлаживавшаяся на одноядерном компьютере.              }
{  Реализованы туннели (funnel) -- сложная версия с блокировками.             }
{  + Начинаю вести подробную историю версий.                                  }

{ 11.2008 Release 0.31/0.33beta                                               }
{  + Введено понятие цепи процедур с повторным входом (вектор, конвеер)       }
{    Автор выражает благодарность доценту Е.И.Ляпунову за идею применения     }
{    процедур с повторным входом для конвеерной обработки.                    }

{ 11.2008 Release 0.22/0.23beta                                               }
{  + Введена корректная поддержка прототипов функций. }

{ 11.2008 Release 0.21beta                                                    }
{  + После дискуссии на RSDN ввел понятие локально статического плана, что    }
{    позволяет реализовать генераторы.                                        }

{ 10.2008 Release 0.2beta                                                     }
{  + Поддержка распараллеливания. Введено понятие статического плана.         }

{ 10.2008 Release 0.1beta                                                     }
{  + Первая версия, без поддержки механизма распараллеливания.                }

{ Предусмотреть ошибки вызова плана -- учесть через define + проверка существования, error }
{ exception при исчерпывании плана... }
{ kept & parallel -- допустить ли }
{ circular chains ??? }
{ фильтр Declared -- по встречающимся, затем цикл уже по ним в строке???
  Но не медленнее ли это будет??? }

program Reenterable;

{$IF (NOT DEFINED(UNIX)) AND (NOT DEFINED(LINUX))}
{$APPTYPE CONSOLE}
{$ENDIF}

{$IFDEF FPC}
{$MODE ObjFPC}
{$ENDIF}
{$H+}

uses
{$IF (DEFINED(UNIX) OR DEFINED(LINUX)) AND DEFINED(FPC)}
  cthreads, cmem,
{$ENDIF}
  SysUtils,
  Classes,
  Math,
  Lexique  in 'LEXIQUE.PAS',
  Evaluat  in 'EVALUAT.PAS',
  Consts   in 'CONSTS.PAS',
  Topo     in 'TOPO.PAS',
  Common   in 'COMMON.PAS',
  Macroses in 'MACROSES.PAS',
  Prolog   in 'PROLOG.PAS',
  Preproc  in 'PREPROC.PAS';

{ OpenCL types translation }
Const NTran = 7;
Const Types: Array[1..NTran] Of PChar =
  ('unsigned long long', 'signed long long', 'long long', 'unsigned long', 'signed long', 'long', 'bool');
Const OCLTypes: Array[1..NTran] Of PChar =
  ('unsigned long', 'signed long', 'long', 'unsigned int', 'signed int', 'int', 'char');

Function OCLMap(Const S:String): String;

Var F: Integer;
Begin
  Result := S;
  For F := 1 To NTran Do
    If Pos(Types[F], Result) <> 0 Then
       Begin
         Result := StringReplace(Result, Types[F], OCLTypes[F], []);
         Exit
       End
End;

Const redVarPrefix = 'red_';

Const redStorePrefix = 'store_';

Type StaticMode = (smDynamic,smStatic,smKept);

Const dcCirc = 1;
      dcList = 2;

Function CollectParamsAfterBracket(L:TAnalyser; Names, Substs:TStringList;
                                   Var PrmDeclaration, RefsDeclaration:String;
                                   Reducts:TStringList;
                                   Var RedDummies,RedModifs:String;
                                   Var _RedDummies,ResetDummies,_RedModifs:String;
                                   Var _pRedDummies,pRedDummies,pRedModifs,pRedModifs_:String;
                                   Var TypeTaskID, NameTaskID, EmptyTaskID:String;
                                   Var InputProcName:String;
                                   Var gpuParams, gpuInit: String;
                                   TypeMaps:TStringList;
                                   LocGlob:TStringList):String;

Var S, S1, Store, Tp, _Tp, Nm, _Nm, Reduct:String;
    CastedFlag: TObject;
    Flag: Boolean Absolute CastedFlag;
    nLocs: Integer;
    F: Integer;
Begin
     Result:='';
     gpuParams := '';
     gpuInit := 'int __idx = plan_vector_id();'+CRLF;
     Names.Clear;
     Substs.Clear;
     If Assigned(LocGlob) Then LocGlob.Clear;
     If (Assigned(Reducts)) Then Reducts.Clear;
     RedDummies:='';
     RedModifs:='';
     _RedDummies:='';
     ResetDummies:='';
     _RedModifs:='';
     pRedDummies:='';
     _pRedDummies:='';
     pRedModifs:='';
     pRedModifs_:='';
     PrmDeclaration:='typedef struct $$$ {'+CRLF+
                     ' unsigned int Flags;'+CRLF;
     RefsDeclaration := '';
     InputProcName:='';
     NameTaskID:='';
     TypeTaskID:='';
     EmptyTaskID:='';
     S1 := L.GetBalancedListItem(True, [RightBracket], @GetLineFromLines) + RightBracket;
     Store := L.AnlzLine;
     L.AnlzLine := S1;
     nLocs := 0;
     While Not (L.Empty Or L.Error Or L.IsNext(RightBracket)) Do
       begin
         S1:=L.GetBalancedListItem(False,[Comma,RightBracket]);
         S:=L.AnlzLine;
         L.AnlzLine:=S1;
         Tp:='';
         Nm:='';
         If Assigned(LocGlob) Then LocGlob.AddObject('', BooleanToTObject(False));
         If (Assigned(Reducts)) And Not L.Empty Then { Reduction XOR Id }
            If L.IsNextIdent(idReduction, True) Then
               Begin
                 L.GetIdent(True);
                 L.Check(LeftBracket);
                 Reducts.Add(L.GetBefore(True,[RightBracket]));
                 L.Check(RightBracket);
                 S1:=L.AnlzLine;
               End
            Else
              Begin
                If L.IsNextIdent(id_local, True) Then
                   Begin
                     L.GetIdent(True);
                     L.Check(LeftBracket);
                     S1 := L.GetBalancedListItem(False,[RightBracket]);
                     If Assigned(LocGlob) Then LocGlob.Strings[LocGlob.Count-1] := S1;
                     L.Check(RightBracket);
                     S1:=L.AnlzLine;
                     Inc(nLocs)
                   End
                Else If L.IsNextIdent(id_global, True) Then
                   Begin
                     L.GetIdent(True);
                     L.Check(LeftBracket);
                     S1 := L.GetBalancedListItem(False,[RightBracket]);
                     If Assigned(LocGlob) Then
                        Begin
                          LocGlob.Strings[LocGlob.Count-1] := S1;
                          LocGlob.Objects[LocGlob.Count-1] := BooleanToTObject(True)
                        End;
                     L.Check(RightBracket);
                     S1:=L.AnlzLine;
                   End;
                Reducts.Add('');
                If L.IsNextIdent(idID, True) Then
                   If Length(NameTaskID)<>0 Then
                      L.MakeError('More than one task ID is declared')
                   Else
                       Begin
                        L.GetIdent(True);
                        L.Check(LeftBracket);
                        EmptyTaskID:=L.GetBalancedListItem(True,[RightBracket]);
                        NameTaskID:=getTaskID;
                        S1:=L.AnlzLine
                       End
              End;
         CastedFlag:=Nil;
         Flag:=False;
         While Not (L.Empty Or L.Error) Do
           begin
             Tp:=Tp+Trim(Nm)+' ';
             Nm:=L.GetBefore(True,[Space,Tabulation]);
             F:=Pos('&',Nm);
             If F>0 Then
                Begin
                  Flag:=True;
                  Delete(Nm,F,1)
                End
           end;
         Tp := Trim(Tp);
         _Tp := '__global ' + OCLMap(Tp);
         _Nm := RandomName;
         If Assigned(LocGlob) Then
            If Length(LocGlob.Strings[LocGlob.Count-1]) = 0 Then
               _Tp := _Tp + ' * '
            Else If Pos('*',Tp) = 0 Then
               L.MakeError('_local/_global parameter is not a pointer');
         If NameTaskID=getTaskID Then
            Begin
              NameTaskID:=Nm;
              TypeTaskID:=Tp
            End;
         If (Assigned(Reducts)) Then
            Begin
              Reduct:=Reducts.Strings[Reducts.Count-1];
              If Reduct<>'' Then
                 If Flag Then
                    Begin
                      RedDummies:=RedDummies+Tp+' '+redVarPrefix+Nm+' = '+Nm+';'+CRLF;
                      _RedDummies:=_RedDummies+Tp+' '+redVarPrefix+Nm+' = '+_Nm+';'+CRLF;
                      _RedDummies:=_RedDummies+Tp+' '+redStorePrefix+Nm+' = '+redVarPrefix+Nm+';'+CRLF;
                      ResetDummies:=ResetDummies+redVarPrefix+Nm+' = '+redStorePrefix+Nm+';'+CRLF;
                      _pRedDummies:=_pRedDummies+Tp+' * __'+redVarPrefix+Nm+' = new '+Tp+'[__num_threads__];'+CRLF;
                      pRedDummies:=pRedDummies+Tp+' '+redVarPrefix+Nm+' = '+Nm+';'+CRLF+
                                               Tp+' & _'+redVarPrefix+Nm+' = __'+redVarPrefix+Nm+'[__thread_id__] = '+Nm+';'+CRLF;
                      If Reduct[1] In IdentSet Then
                         Begin
                           RedModifs:=RedModifs+Nm+' = '+Reduct+'('+Nm+','+redVarPrefix+Nm+');'+CRLF;
                           _RedModifs:=_RedModifs+_Nm+' = '+Reduct+'('+_Nm+','+redVarPrefix+Nm+');'+CRLF;
                           pRedModifs:=pRedModifs+'_'+redVarPrefix+Nm+' = '+Reduct+'(_'+redvarPrefix+Nm+','+redVarPrefix+Nm+');'+CRLF;
                           pRedModifs_:=pRedModifs_+'for (int __proc__=0; __proc__<__num_threads__; __proc__++) '+
                                                    Nm+' = '+Reduct+'(__'+redvarPrefix+Nm+'[__proc__],'+Nm+');'+CRLF
                         End
                      Else
                         Begin
                           RedModifs:=RedModifs+Nm+Reduct+'= '+redVarPrefix+Nm+';'+CRLF;
                           _RedModifs:=_RedModifs+_Nm+Reduct+'= '+redVarPrefix+Nm+';'+CRLF;
                           pRedModifs:=pRedModifs+'_'+redVarPrefix+Nm+Reduct+'= '+redVarPrefix+Nm+';'+CRLF;
                           pRedModifs_:=pRedModifs_+'for (int __proc__=0; __proc__<__num_threads__; __proc__++) '+
                                                    Nm+Reduct+'= __'+redVarPrefix+Nm+'[__proc__];'+CRLF
                         End;
                      pRedModifs_:=pRedModifs_+'delete[] __'+redVarPrefix+Nm+';'+CRLF
                    End
                 Else
                    L.MakeError('Reduction parameter '''+Nm+''' must be passed by reference')
            End
         Else
            Reduct:='';
         Names.AddObject(Nm,CastedFlag);
         Substs.Add(_Nm);
         L.AnlzLine := Trim(Tp);
         If L.IsNextIdent(idConst, True) Then
            L.CheckIdent(idConst, True);
         Tp := L.AnlzLine;
         If L.IsNextIdent(idInput_Proc, True) Then
            Begin
              L.CheckIdent(idInput_Proc, True);
              If L.Empty Then
                 InputProcName := Trim(Nm);
              L.AnlzLine := Tp;
            End;
         PrmDeclaration:=PrmDeclaration+
            L.AnlzLine+' '+Trim(Nm)+';'+CRLF;
         RefsDeclaration:=RefsDeclaration+
            L.AnlzLine+' &'+Trim(Nm)+',';
         L.AnlzLine:=S;
         Result:=Result+S1;
         gpuParams := gpuParams + Trim(_Tp) + ' ' + Trim(_Nm);
         If L.IsNext(Comma) Then
            Begin
              L.Check(Comma);
              Result:=Result+Comma;
              gpuParams := gpuParams + Comma
            End;
         If Assigned(LocGlob) Then
            If Length(LocGlob.Strings[LocGlob.Count-1]) > 0 Then
               Begin
                 gpuInit := gpuInit + '__global ' + OCLMap(Tp) + ' ' + Nm + ' = ';
                 If Boolean(TObjectToInteger(LocGlob.Objects[LocGlob.Count-1])) Then // _global(N)
                    gpuInit := gpuInit + _Nm + ';' + CRLF
                 Else // local(N)
                    gpuInit := gpuInit + '&' + _Nm + '[__offs[__idx*###+'+IntToStr(nLocs-1)+']];' + CRLF
               End
            Else
               gpuInit := gpuInit + OCLMap(Tp) + ' ' + Nm + ' = ' + _Nm + '[__idx];'+CRLF
       end;
     If Length(Result)<>0 Then
        Result:=','+Result;
     Result:=Result+RightBracket;
     gpuParams := Trim(gpuParams);
     gpuInit := StringReplace(gpuInit, '###', IntToStr(nLocs), [rfReplaceAll]);
     If (Length(gpuParams) > 0) And (gpuParams[Length(gpuParams)] <> LeftBracket) Then
        gpuParams := gpuParams + Comma;
     gpuParams := gpuParams + ' __global int * __offs';
     L.Check(RightBracket);
     L.AnlzLine := Store;
     L.DelSpaces;
     If (Length(NameTaskID)<>0) And Assigned(TypeMaps) Then
        If L.Empty Or L.IsNextSet([SemiColon,LeftFBracket]) Then
           Begin
             S:=L.AnlzLine;
             L.AnlzLine:=TypeTaskID;
             If (L.FindIdent(True)=idStruct) Or (L.FindIdent(True)=idUnion) Then
                Begin
                  S1:=L.GetBefore(True,[Space,Tabulation])+' ';
                  L.DelSpaces
                End
             Else
                S1:='';
             S1:=S1+L.GetBefore(True,[Space,Tabulation,'*']);
             If L.IsNext('*') Then
                S:=StringReplace(TypeMaps.Values[S1],'$','->',[rfReplaceAll])+' '+S
             Else
                S:=StringReplace(TypeMaps.Values[S1],'$','.',[rfReplaceAll])+' '+S;
             L.AnlzLine:=StringReplace(S,'@@','('+EmptyTaskID+')',[rfReplaceAll])
           End;
     PrmDeclaration := PrmDeclaration +
        ' $$$() { Flags = 0; };' + CRLF;
     If (Length(RefsDeclaration) > 0) Then
        Delete(RefsDeclaration, Length(RefsDeclaration), 1)
End;

Function tran(Names, Substs: TStringList; Const Nm: String): String;

Var K: Integer;
Begin
  K := Names.IndexOf(Nm);
  If K < 0 Then
     Begin
       WriteLn('No substitution to ', Nm);
       Halt(-1)
     End;
  Result := Substs.Strings[K]
End;

Procedure CorrectParamNames(Var ParamNames,S:String);
Begin
     If Length(ParamNames)>0 Then
        Begin
          ParamNames[Length(ParamNames)]:=')';
          ParamNames:='__nprocs__,'+ParamNames
        End
     Else
        ParamNames:='__nprocs__)';
     S:=ParamNames;
     ParamNames:=','+ParamNames
End;

Function CheckOneArgPredicate(Var Out:String; L:TAnalyser; Const Types,Names: Array Of String; Const ID,TypeValue,Name,Init,redOp,TmplVal:String; Var Arg:String):Boolean;

Var S, Enum: String;
    F: Integer;
Begin
     Result:=L.IsNextIdent(Name, True);
     If Result Then
        Begin
          L.GetIdent(True);
          If L.Check(LeftBracket) Then
             If (Not L.IsNext(LeftSqrBracket)) Or (Length(TypeValue)=0) Then
                Arg:=StringReplace(TmplVal,'$$',L.GetBalancedListItem(True,[RightBracket],@GetLineFromLines),[rfReplaceAll])
             Else
                Begin
                  L.Check(LeftSqrBracket);
                  Enum:=L.GetBalancedListItem(True,[RightSqrBracket],@GetLineFromLines);
                  Arg:=L.GetBalancedListItem(True,[RightBracket],@GetLineFromLines);
                  S:='';
                  For F:=Low(Types) To High(Types) Do
                      S:=S+Types[F]+' '+Names[F]+',';
                  SetLength(S,Length(S)-1);
                  Out:=Out+'inline '+TypeValue+' '+ID+'_'+Name+'('+S+') {'+CRLF;
                  If CompareText(TypeValue,'void')<>0 Then
                     Begin
                       Out:=Out+'  '+TypeValue+' result = '+Init+';'+CRLF;
                       If redOp='&=' Then
                          Out:=Out+'  '+Enum+' if (!(result '+redOp+' '+StringReplace(TmplVal,'$$',Arg,[rfReplaceAll])+')) break;'+CRLF
                       Else If redOp='|=' Then
                          Out:=Out+'  '+Enum+' if (result '+redOp+' '+StringReplace(TmplVal,'$$',Arg,[rfReplaceAll])+') break;'+CRLF
                       Else
                          Out:=Out+'  '+Enum+' result '+redOp+' '+StringReplace(TmplVal,'$$',Arg,[rfReplaceAll])+';'+CRLF;
                       Out:=Out+'  return result;'+CRLF
                     End
                  Else
                     Out:=Out+'  '+Arg+';'+CRLF;
                  Out:=Out+'}'+CRLF;
                  S:='';
                  For F:=Low(Types) To High(Types) Do
                      S:=S+Names[F]+',';
                  SetLength(S,Length(S)-1);
                  Arg:=ID+'_'+Name+'('+S+')'
                End
        End
End;

Procedure CollectTypeName(L:TAnalyser; Var Tp,Nm:String);
Begin
     Tp:='';
     Nm:='';
     While Not (L.Empty Or L.Error Or L.IsNext(SemiColon)) Do
       begin
         Tp:=Tp+Nm+' ';
         Nm:=L.GetBefore(False,[Space,Tabulation,SemiColon]);
         L.DelSpaces
       end;
     L.Check(SemiColon);
End;

Function AnalyzeType(Var L:TAnalyser; IsMarkup: Boolean;
                     Var TagID: String; Var S:String): String;

Var S1,S2,S3,PtrID,ID: String;
    InactiveState, ActiveState, NameState: String;
    Prereqs: TStringList;
    ObjFlag: TObject;
    BoolFlag: Boolean Absolute ObjFlag;
    Tp, Nm: String;
    F: Integer;
Begin
     L.AnlzLine:=S;
     S1:=L.GetBalancedListItem(True,[SemiColon],@GetLineFromLines);
     S:=L.AnlzLine;
     L.AnlzLine:=S1;
     L.DelSpaces;
     S1:=L.GetBefore(False,[Space,Tabulation]);
     TagID:=L.GetBefore(True,[Space,Tabulation,LeftFBracket]);
     If L.IsNext(LeftFBracket) Then
        Begin
          S1:=S1+' '+TagID+' '+LeftFBracket;
          PtrID:='';
          TagID:=''
        End
     Else
        Begin
          TagID:=Trim(TagID+' '+L.GetBefore(True,[LeftFBracket]));
          PtrID:=TagID+' *';
          S1:=S1+' '+TagID+' '+LeftFBracket;
        End;
     L.Check(LeftFBracket);
     InactiveState:='';
     ActiveState:='';
     NameState:='';
     Tp:=''; Nm:='';
     Prereqs:=TStringList.Create;
     While Not (L.Error Or L.Empty Or L.IsNext(RightFBracket)) Do
       If L.FindIdent(True)=idPre_id Then
          Begin
            L.GetIdent(True);
            CollectTypeName(L,Tp,Nm);
            S3:=Trim(Tp);
            If Length(TagID)<>0 Then
               If (TagID<>S3) And (PtrID<>S3) Then
                  L.MakeWarning(Format('pre_id specification "%s" is not tag definition "%s" or reference "%s *"',[S3,TagID,TagID]));
            ObjFlag:=Nil;
            BoolFlag:=S3[Length(S3)]='*';
            Prereqs.AddObject(Nm,ObjFlag);
            S1:=S1+' '+Tp+' '+Nm+';'
          End
       Else If L.FindIdent(True)=idState Then
          Begin
            L.GetIdent(True);
            If L.Check(LeftBracket) Then
               Begin
                 InactiveState:=L.GetBalancedListItem(True,[Comma]);
                 ActiveState:=L.GetBalancedListItem(True,[RightBracket]);
                 CollectTypeName(L,Tp,Nm);
                 NameState:=Nm;
                 S1:=S1+' '+Tp+' '+Nm+';'
               End
          End
       Else
          S1:=S1+' '+L.GetBalancedListItem(True,[SemiColon])+';';
     If Not L.Error Then L.Check(RightFBracket);
     If Not IsMarkup Then
        S:=S1+'} '+L.AnlzLine+';'+S;
     Result:='';
     With Prereqs Do
       If Count>0 Then
          Begin
            S2:=LowerCase(idDepends)+'(';
            Result:=LowerCase(idIf)+'(';
            ID:=LowerCase(idID)+'$';
            For F:=0 To Count-1 Do
              Begin
                Result:=Result+'('+ID+Strings[F]+'==@@';
                If Boolean(TObjectToInteger(Objects[F])) Then
                   S3:='->'
                Else
                   S3:='.';
                If Length(NameState)<>0 Then
                   Result:=Result+' || '+ID+Strings[F]+S3+NameState+'=='+ActiveState+')'
                Else
                   Result:=Result+')';
                S2:=S2+ID+Strings[F];
                If F<Count-1 Then
                   Begin
                     Result:=Result+' && ';
                     S2:=S2+','
                   End
              End;
            Result:=Result+') '+S2+') '
          End;
     If Length(NameState)<>0 Then
        Result:=Result+LowerCase(idSet)+'('+ID+NameState+'='+ActiveState+') '+
                       LowerCase(idReset)+'('+ID+NameState+'='+InactiveState+') ';
     Prereqs.Free
End;

Procedure AnalyzeBrackets(Const FID: String; Const S: String; Var FirstBracketIsRead: Boolean; Var ReadFunctionLevel: Integer);

Var F:Integer;
begin
     For F := 1 To Length(S) Do
       If S[F] = LeftFBracket Then
          begin
            FirstBracketIsRead := True;
            Inc(ReadFunctionLevel)
          end
       Else If S[F] = RightFBracket Then
          begin
            Dec(ReadFunctionLevel);
            If ReadFunctionLevel < 0 Then
               begin
                 WriteLn('Function ', FID, ' termination "}" is not in the single line',TLine(Lines.Objects[LCounter-1]).GetDescription);
                 Halt
               end
          end
end;

Function WriteStructDeclaration(Var Out: TextFile; IDList, DeclarationList: TStringList; Const PrmDeclaration, PrmStruct: String): String;

Var Idx: Integer;
Begin
  Idx:=DeclarationList.IndexOf(PrmDeclaration);
  If Idx < 0 Then
     Begin
       DeclarationList.AddObject(PrmDeclaration, TObject(NewStr(PrmStruct)));
       WriteLn(Out,StringReplace(PrmDeclaration, '$$$', PrmStruct, [rfReplaceAll]),' ',PrmStruct,';');
       IDList.AddObject(PrmStruct, IntegerToTObject(0));
       Result := PrmStruct
     End
  Else
     Begin
       Result := PString(DeclarationList.Objects[Idx])^;
       WriteLn(Out,'#define ',PrmStruct,' ',Result)
     End
End;

Procedure HandleChains(Var Out: TextFile; L, L1: TAnalyser; Var S: String;
                       Var ClusteredArrID: String; Chain: TStringList);

Var S1, S2, S3: String;
    Start: Integer;
    Parallelize: String;
    ChainInit: String;
    ID: String;
    NProcs: String;
    ChainItems: TStringList;
    Links: TLinks;
    Num: String;
    Vectorize: Boolean;
    Idx: Real;
    Flag: Boolean;
    Found: Boolean;
    F, G, Q: Integer;
Begin
  ChainItems:=TStringList.Create;

  Start:=1;
  Repeat // plan_chain / plan_parallel_chain
    F:=AnsiPos(idplan_chain,UpperCase(Copy(S,Start,Length(S))));
    Parallelize:='0';
    If F=0 Then
       Begin
         F:=AnsiPos(idplan_parallel_chain,UpperCase(Copy(S,Start,Length(S))));
         If F>0 Then
            Begin
              S1:=idplan_parallel_chain;
              Parallelize:='1'
            End
       End
    Else
       Begin
         If Length(ClusteredArrID)>0 Then
            Begin
              WriteLn('Warning: "'+idclustered+'" ignored on "'+idplan_chain,TLine(Lines.Objects[LCounter-1]).GetDescription);
              ClusteredArrID := ''
            End;
         S1:=idplan_chain
       End;
    If F>0 Then
       Begin
         Inc(F,Start-1);
         L.AnlzLine:=Copy(S,F+Length(S1),Length(S));
         If L.IsNext(LeftBracket) And Not InQuotes(S, F-1, DblQuote) Then
            Begin
              L.Check(LeftBracket);
              ChainInit:=L.GetBalancedListItem(False,[Comma],@GetLineFromLines);
              L.Check(Comma);
              If L.Error Then Break;
              S2 := L.GetBalancedListItem(True,[RightBracket],@GetLineFromLines) + RightBracket;
              S3 := L.AnlzLine;
              L.AnlzLine := S2;
              ChainItems.Clear;
              // count args -- create adequate macros??? Output to list???
              // recursive macros
              S2:=L.FindIdent(False);
              Vectorize:=Chain.IndexOf(S2)<0;
              If Vectorize Then
                 Begin
                   Num:=L.GetBalancedListItem(False,[Comma]);
                   L.Check(Comma);
                   ChainItems.AddObject(_TrimRight(L.GetBalancedListItem(False,[RightBracket])),IntegerToTObject(1))
                 End
              Else
                 While Not (L.IsNext(RightBracket) Or L.Empty Or L.Error) Do
                   Begin
                     S2:=L.GetIdent(False);
                     If L.IsNext(LeftSqrBracket) Then
                        Begin
                          L.Check(LeftSqrBracket);
                          Idx := 0.0;
                          L.GetNumber(True, Idx);
                          L.Check(RightSqrBracket)
                        End
                     Else
                        Idx := 1.0;
                     With ChainItems Do
                       Begin
                         Q := 0;
                         Found := False;
                         While (Q < Count) And Not Found Do
                           Begin
                             L1.AnlzLine := Strings[Q];
                             If (L1.GetIdent(False) = S2) And (TObjectToInteger(Objects[Q])=Round(Idx)) Then
                                Found := True
                             Else
                                Inc(Q)
                           End;
                         If Found Then
                            Begin
                              WriteLn('Conveyor/vector: more than one ',S2,'[',Round(Idx),']',TLine(Lines.Objects[LCounter-1]).GetDescription);
                              Exit
                            End;
                         AddObject(S2+_TrimRight(L.GetBalancedListItem(False,[RightBracket,Dash,Comma])),IntegerToTObject(Integer(Round(Idx))))
                       End;
                     If L.IsNext(Comma) Then
                        L.Check(Comma)
                     Else If L.IsNext(Dash) Then
                       Begin
                         L.Check(Dash); L.Check(Greater)
                       End
                   End;
              L.Check(RightBracket);
              With ChainItems Do
                For G := 0 To Count - 1 Do
                  Begin
                    L.AnlzLine := Strings[G];
                    ID := L.GetIdent(False);
                    L.Check(LeftBracket);
                    S2 := L.GetBalancedListItem(True,[RightBracket]);
                    NProcs := '0';
                    If L.IsNext(Slash) Then
                       Begin
                         L.Check(Slash);
                         NProcs := Trim(L.AnlzLine)
                       End;
                    S2 := Trim(S2);
                    If Length(S2) > 0 Then
                       S2 := Comma + S2;
                    Strings[G] := ID + LeftBracket + NProcs + S2 + RightBracket
                  End;
              L.AnlzLine := S3;
              G:=Length(S)-Length(TrimLeft(S));
              WriteLn(Out,Copy(S,1,F-1));
              NProcs := '';
              Flag:=L.IsNext(SemiColon);
              If Flag Then
                 L.Check(SemiColon)
              Else If L.IsNext(Slash) Then
                Begin
                  L.Check(Slash);
                  NProcs := L.GetBalancedListItem(True,[SemiColon],@GetLineFromLines);
                  Flag:=True
                End;
              S2:=L.AnlzLine;

              SetLength(Links, 0);
              S1 := GenerateTopology(False, ClusteredArrID, Parallelize, ChainInit,
                                     NProcs, Num, Vectorize,
                                     Chain, ChainItems,
                                     Links);

              If Flag Then S1:=S1+SemiColon;

              WriteLn(Out,S1);
              S:=StringOfChar(' ',G)+S2;
              Start:=1
            End
         Else
            Start:=F+Length(S1)
       End
  Until (F=0) Or L.Error;

  ChainItems.Free
End;

Procedure HandleProcMentions(L, L1: TAnalyser; Declared: TStringList; Var S: String);

Var S1, S2: String;
    Indexing: String;
    Handled: Boolean;
    C : Char;
    F, G, H: Integer;
Begin
  // plan_proc()/NP, *plan_proc, *plan_proc<<[...], plan_proc[expr]
  G:=0;
  With Declared Do
    While (G<Count) And Not L.Error Do
      Begin
        H := 1;
        Repeat
          F:=Pos(Strings[G],Copy(S,H,Length(S)));
          If F>0 Then
             Begin
               If ((H+F-2>0) And (S[H+F-2] In IdentSet)) Or
                  ((H+F-1+Length(Strings[G])<=Length(S)) And (S[H+F-1+Length(Strings[G])] In IdentSet)) Then
                  begin
                    H := H + F;
                    F := 0
                  end
             End
          Else
             Break
        Until F > 0;
        If F > 0 Then
           Begin
            F := H+F-1;
            L.AnlzLine:=Copy(S,F+Length(Declared.Strings[G]),Length(S));
            If InQuotes(S, F-1, DblQuote) Then
               S := Copy(S, 1, F-1) + #0+Chr(G And $0F)+Chr((G Shr 4) And $0F)+Chr((G Shr 8) And $0F)+Chr((G Shr 12) And $0F) + Copy(S, F+Length(Strings[G]), Length(S))
            Else If (F > 1) And (S[F-1] = Asterisk) Then
               Begin
                 L.AnlzLine := Copy(S, F+Length(Strings[G]), Length(S));
                 S := Copy(S, 1, F-2) + 'plan(' + #0+Chr(G And $0F)+Chr((G Shr 4) And $0F)+Chr((G Shr 8) And $0F)+Chr((G Shr 12) And $0F) + ')';
                 If L.IsNextSet([Less, Greater]) Then
                    Begin
                      C := L.AnlzLine[1];
                      L.Check(C);
                      If L.IsNext(C) Then
                         Begin
                           L.Check(C);
                           If L.IsNext(LeftSqrBracket) Then
                              Begin
                                 L.Check(LeftSqrBracket);
                                 S1 := Trim(L.GetBalancedListItem(True, [RightSqrBracket], @GetLineFromLines));
                                 If Length(S1) > 0 Then
                                    Begin
                                      S := S + C + C + '( (__obj_list__()';
                                      L1.AnlzLine := S1 + Comma;
                                      While Not (L.Error Or L1.Error Or L1.Empty) Do
                                        Begin
                                          S1 := Trim(L1.GetBalancedListItem(True, [Comma]));
                                          If Length(S1) = 0 Then
                                             L.MakeError('"_", number, string or variable/array expected')
                                          Else If S1 = Underscore Then
                                             S := S + '<<__obj_empty__().get_data()'
                                          Else If S1[1] In IntNumberSet+[Point] Then
                                             S := S + '<<(' + S1 + ')'
                                          Else If S1[1] In [Quote, DblQuote] Then
                                             S := S + '<<' + S1
                                          Else If S1[1] In IdentSet Then
                                             Begin
                                               F := 2;
                                               While (F <= Length(S1)) And (S1[F] In IdentSet) Do
                                                 Inc(F);
                                               If F > Length(S1) Then
                                                  S := S + '<<__obj_var__(&' + S1 + ',sizeof(' + S1 + ')).get_data()'
                                               Else
                                                  Begin
                                                    S2 := Copy(S1, 1, F-1);
                                                    S := S + '<<__obj_array__(reinterpret_cast<void *>('+ S2 + '),';
                                                    G := 0;
                                                    While (F < Length(S1)) And Not L.Error Do
                                                      If (S1[F] = LeftSqrBracket) And (S1[F+1] = RightSqrBracket) Then
                                                         Begin
                                                           Inc(G);
                                                           Inc(F,2)
                                                         End
                                                      Else
                                                         L.MakeError('Series of [] expected after "'+S2+'"');
                                                    S := S + IntToStr(G) + ',';
                                                    S1 := S2;
                                                    For F := 1 To G Do
                                                        S1 := S1 + '[0]';
                                                    S := S + 'sizeof(' + S1 + '), sizeof(' + S2 + ')';
                                                    S := S + ').get_data()'
                                                  End
                                             End
                                          Else
                                             L.MakeError('"_", number, string or variable/array expected')
                                        End;
                                      S := S + ').get_items() )'
                                    End
                              End
                           Else
                              S := S + C + C
                         End
                      Else
                         S := S + C
                    End;
                 S := S + L.AnlzLine
               End
            Else If (F > 1) And (S[F-1] = Ampersand) Then
               S := Copy(S, 1, F-2) + '&_call_' + #0+Chr(G And $0F)+Chr((G Shr 4) And $0F)+Chr((G Shr 8) And $0F)+Chr((G Shr 12) And $0F) + Copy(S, F+Length(Strings[G]), Length(S))
            Else
              Begin
                Indexing:='';
                Handled:=False;
                If L.IsNext(LeftSqrBracket) Then
                   Begin
                     L.Check(LeftSqrBracket);
                     S1:=_TrimRight(L.GetBalancedListItem(True,[RightSqrBracket]));
                     Indexing:='['+S1+']';
                     If Not L.IsNext(LeftBracket) Then // 'Proc[idx]...' case.
                        Begin
                           S:=Copy(S,1,F-1)+'((((unsigned long long)&_call_'+#0+
                              Chr(G And $0F)+Chr((G Shr 4) And $0F)+Chr((G Shr 8) And $0F)+Chr((G Shr 12) And $0F)+
                              ')<<32)+('+S1+')';
                           S:=S+')'+L.AnlzLine;
                           Handled := True;
                        End
                   End;
                 If Not Handled Then
                   If L.IsNext(LeftBracket) Then
                     Begin
                       L.Check(LeftBracket);
                       If L.IsNext(LeftSqrBracket) Then // proc([params]) -- continue equivalent
                          Begin
                            L.Check(LeftSqrBracket);
                            S1:=_TrimRight(L.GetBalancedListItem(True,[RightSqrBracket],@GetLineFromLines));
                            L.Check(RightBracket);
                            S:=Copy(S,1,F-1)+'__continue__'+#0+Chr(G And $0F)+Chr((G Shr 4) And $0F)+Chr((G Shr 8) And $0F)+Chr((G Shr 12) And $0F)+Indexing+LeftBracket;
                          End
                       Else
                          Begin
                            S1:=_TrimRight(L.GetBalancedListItem(True,[RightBracket],@GetLineFromLines));
                            S:=Copy(S,1,F-1)+#0+Chr(G And $0F)+Chr((G Shr 4) And $0F)+Chr((G Shr 8) And $0F)+Chr((G Shr 12) And $0F)+Indexing+LeftBracket;
                          End;
                       If L.IsNext(Slash) Then
                          Begin
                            L.Check(Slash);
                            If L.IsNext(LeftBracket) Then
                               Begin
                                 L.Check(LeftBracket);
                                 S2:=L.GetBalancedListItem(True,[RightBracket])
                               End
                            Else If L.IsNextSet(IntNumberSet) Then
                               S2:=L.GetSequence(IntNumberSet, False)
                            Else
                               S2:=L.GetSequence(IdentSet+['.'], False)
                          End
                       Else
                          S2:='0';
                       S:=S+S2;
                       If Length(_TrimRight(S1)) > 0 Then
                          S:=S+',';
                       S:=S+S1+RightBracket+L.AnlzLine
                     End
                   Else
                     S := Copy(S, 1, F-1) + #0+Chr(G And $0F)+Chr((G Shr 4) And $0F)+Chr((G Shr 8) And $0F)+Chr((G Shr 12) And $0F) + Copy(S, F+Length(Strings[G]), Length(S))
              End
           End
        Else
           Inc(G)
      End;
  Repeat
    F:=Pos(#0,S);
    If F<>0 Then
       S:=Copy(S,1,F-1)+
          Declared.Strings[Ord(S[F+1])+(Ord(S[F+2]) Shl 4)+(Ord(S[F+3]) Shl 8)+(Ord(S[F+4]) Shl 12)]+
          Copy(S,F+5,Length(S))
  Until F=0
End;

Procedure HandleContinues(L: TAnalyser; Var S: String);

Var Start: Integer;
    F, G: Integer;
Begin
  Start:=1;
  Repeat // continue plan_proc
    F:=AnsiPos(idContinue,UpperCase(Copy(S,Start,Length(S))));
    If F>0 Then
       Begin
         Inc(F,Start-1);
         G:=F+Length(idContinue);
         If ((F=1) Or (S[F-1] In [Space,Tabulation,SemiColon])) And
            (G<Length(S)) And (S[G] In [Space,Tabulation]) And
            Not InQuotes(S, F-1, DblQuote) Then
            Begin
              L.AnlzLine:=Copy(S,G,Length(S));
              If Not L.IsNext(SemiColon) Then
                 S:=Copy(S,1,F-1)+'__continue__'+L.AnlzLine
            End;
         Start:=G+1
       End
  Until (F=0) Or L.Error
End;

Procedure HandlePlansThrows(L: TAnalyser; Var S: String);

Var S1, S2, S3: String;
    Start: Integer;
    F, G: Integer;
Begin
  Start:=1;
  Repeat // plan_(first|last), throw_(first|last)
    G:=Low(Plans);
    F:=0;
    While (F=0) And (G<=High(Plans)) Do
      Begin
        F:=AnsiPos(Plans[G],UpperCase(Copy(S,Start,Length(S))));
        If F=0 Then
           Inc(G)
      End;
    If F>0 Then
       Begin
         Inc(F,Start-1);
         L.AnlzLine:=Copy(S,F+Length(Plans[G]),Length(S));
         If L.IsNext(LeftBracket) And Not InQuotes(S, F-1, DblQuote) Then
            Begin
              S:=Copy(S,1,F+Length(Plans[G])-1)+LeftBracket;
              L.Check(LeftBracket);
              S2 := L.GetBalancedListItem(True,[RightBracket],@GetLineFromLines) + RightBracket;
              S3 := L.AnlzLine;
              L.AnlzLine := S2;
              G:=0;
              While Not (L.IsNext(RightBracket) Or L.Empty Or L.Error) Do
                Begin
                  S1:=_TrimRight(L.GetBalancedListItem(False,[RightBracket,Comma]));
                  G:=G*2;
                  If S1[Length(S1)]=Exclamation Then
                     Begin
                       SetLength(S1,Length(S1)-1);
                       Inc(G)
                     End;
                  S:=S+S1;
                  If L.IsNext(Comma) Then
                     Begin
                       L.Check(Comma);
                       S:=S+Comma
                     End
                End;
              Start:=Length(S)+1;
              L.AnlzLine := L.AnlzLine + S3;
              S:=S+','+IntToStr(G)+L.AnlzLine
            End
         Else
            Start:=F+Length(S1)
       End
  Until (F=0) Or L.Error
End;

Function CheckCommandLine(Defines: TStringList; Var FollowDefs, NoSourceLines, ExtensionsOnly: Boolean): Integer;

Var S: String;
    F: Integer;
Begin
  FollowDefs := False;
  ExtensionsOnly := False;
  Result := 1;
  NoSourceLines := False;
  While (Result <= ParamCount) And
        (Length(ParamStr(Result)) >= 3) And
        (ParamStr(Result)[1] = Dash) Do
     Begin
       S := ParamStr(Result);
       If S[2] = 'D' Then
          Begin
            F := Pos(Equal, S);
            If F > 0 Then
               Defines.AddObject(Copy(S, 3, F - 3), TObject(NewStr(Copy(S, F + 1, Length(S)))))
            Else
               Defines.AddObject(Copy(S, 3, Length(S)), TObject(NewStr('1')))
          End
       Else If Copy(S, 2, Length('followdefines')) = 'followdefines' Then
          FollowDefs := True
       Else If Copy(S, 2, Length('extensionsonly')) = 'extensionsonly' Then
          ExtensionsOnly := True
       Else If Copy(S, 2, Length('nosourcelines')) = 'nosourcelines' Then
          NoSourceLines := True
       Else
         Begin
           WriteLn('Unknown parameter ', S);
           Halt(-1)
         End;
       Inc(Result)
     End
End;

Var Inp, Out: TextFile;
    OldName, NewName: String;
    Defines: TStringList;
    NoSourceLines: Boolean;
    S, S1, rS1, S2, oEvs, Evs, Proc, PrmStruct, ThrStruct, Params, gpuParams, ParamNames, _ParamNames,
    ParamAsgns, ParamReasgns, STParamReasgns,
    ParamDummy, ParamDummies, STParamDummies, SoftSTParamDummies,
    rParamNames, _rParamNames, rParamDummies,
    GetAsgns,
    gpuInit: String;
    NMParams: String;
    ThrParamAsgns, ThrParamNames, _ThrParamNames,
    PrmDeclaration, RefsDeclaration, ThrDeclaration,
    RedDummies, _RedDummies, RedModifs, _RedModifs, eRedDummies, _eRedDummies, eRedModifs, _eRedModifs,
    _pRedDummies, pRedDummies, pRedModifs, pRedModifs_, ResetDummies,
    Ldecl, Lparm, Lfmt,
    TypeID, ID: String;
    LocGlobs: TStringList;
    InputProcName: String;
    ClusteredArrID: String;
    GlueSymbol: String;
    TagID: String;
    TypeTaskID, NameTaskID: String;
    RetAssgn: String;
    TaskIf, TaskSet, TaskReset, d_eli, TaskEmpty: String;
    Declared, Chain, _Names, Substs, ChainNames, ChainSubsts, Reducts, TypeMaps: TStringList;
    TaskDependsList: TStringList;
    Topology: TStringList;
    IsClustered, IsVectorized: Boolean;
    SL: TStringList;
    ProgGPU: TStringList;
    FL: TStringList;
    Restrictions: TRestrictions;
    F,G,K,Q: Integer;
    LFlag: Integer;
    L,L1: TAnalyser;
    DeclarationList: TStringList;
    IDList: TStringList;
    RealType: String;
    IsDeclaration: Boolean;
    IsMarkup:  Boolean;
    ChainMode: Boolean;
    ReadFunction: Boolean;
    FunctionType, FunctionID: String;
    FunctionText, SoftFunctionText, GPUFunctionText: String;
    FunctionThrowParams: String;
    FunctionParamNames: String;
    FirstBracketIsRead: Boolean;
    ReadFunctionLevel: Integer;
    AutosInserted: Boolean;
    PureAutos, PlanAutos, PureDummies: String;
    AtomizeFlag, SoftAtomizeFlag, VectorizeFlag: Boolean;
    StaticFlag: StaticMode;
    CastedFlag: TObject;
    FollowDefs: Boolean;
    ExtensionsOnly: Boolean;
    ParamNameNum: Integer;
    Flag: Boolean Absolute CastedFlag;
begin
     If ParamCount=0 Then
        Begin
          WriteLn('Planning C (R) Translator V0.94beta3');
          WriteLn('free for any purposes. Original author: V.V.Pekunov, 2008-2017, 2019-2021');
          WriteLn('Usage: Reenterable.exe [-nosourcelines] [-extensionsonly] [-followdefines] [-Dmacro[=val]] <inputfile.cpp> [outputfile]');
          WriteLn('   -nosourcelines    Removes references to source line numbers, therefore');
          WriteLn('                     C++ compiler will use the line numbers from the generated file,');
          WriteLn('                     not from the source file. Useful in Planning C Translator debugging!');
          WriteLn('   -extensionsonly   Do not include Planning C preambule and internal functions. ');
          WriteLn('                     This mode can be used as a C++ Extensions Only Mode, where only the');
          WriteLn('                     scanners/parsers/deductive modules are used.');
          WriteLn('   -followdefines    If used then the translator performs conditional');
          WriteLn('                     preprocessing using directives define, undef, if and so on.');
          WriteLn('                     Only an active lines are put into the resulting code.');
          WriteLn('   -Dmacro[=val]     Defines macro symbols. It can be very useful when your code');
          WriteLn('                     depends on the symbols that are defined by your main compiler');
          WriteLn('                     but aren''t known to this translator, e.g. _WIN32, _OPENMP ...')
        End
     Else
        Begin
          ChDir(ExcludeTrailingBackSlash(ExtractFilePath(ParamStr(0))));

          Defines := TStringList.Create;

          ParamNameNum := CheckCommandLine(Defines, FollowDefs, NoSourceLines, ExtensionsOnly);

          If ParamCount = ParamNameNum Then
             Begin
               OldName:=ChangeFileExt(ParamStr(ParamNameNum),'.bak');
               NewName:=ParamStr(ParamNameNum);
               SysUtils.DeleteFile(OldName);
               RenameFile(NewName,OldName);
             End
          Else
             Begin
               OldName:=ParamStr(ParamNameNum);
               NewName:=ParamStr(ParamNameNum+1)
             End;

          Assign(Inp,OldName);
          Try
             Reset(Inp);
          Except
             WriteLn('Can''t open input file ', OldName, ' for reading');
             Halt(-1)
          End;
          If FileExists(NewName) Then
             Begin
               S := ChangeFileExt(NewName, '.bak');
               SysUtils.DeleteFile(S);
               RenameFile(NewName, S)
             End;
          Assign(Out,NewName);
          Try
             Rewrite(Out);
          Except
             WriteLn('Can''t open output file ', NewName, ' for writing');
             Halt(-1)
          End;

          LineDelimiter := '';

          L:=TAnalyser.Create(IdentSet,[Space,Tabulation]);
          L1:=TAnalyser.Create(IdentSet,[Space,Tabulation]);

          PassCount := 0;
          PreprocPasses := 1;
          Repeat
            WriteLn('Preprocessing: Pass [', PassCount+1, ']');
            If PassCount > 0 Then
               begin
                 With Defines Do
                   Begin
                     For F := 0 To Count - 1 Do
                         DisposeStr(PString(Objects[F]));
                     Clear;

                     CheckCommandLine(Defines, FollowDefs, NoSourceLines, ExtensionsOnly)
                   End;
                 With Lines Do
                   Begin
                     For F := 0 To Count - 1 Do
                         If Assigned(Objects[F]) Then
                            Objects[F].Free;
                     Free
                   End;
                 With Files Do
                   Begin
                     For F := 0 To Count - 1 Do
                         If Assigned(Objects[F]) Then
                            Objects[F].Free;
                     Free
                   End;
                 ProgGPU.Free;
                 Reset(Inp)
               end;
            Lines := TStringList.Create;
            // Preprocessing
            CommentFlag := False;
            // Read file into Lines
            Files := TStringList.Create;
            F := 1;
            While Not Eof(Inp) Do
              Begin
                ReadLn(Inp,S);
                StripComments(S, CommentFlag);
                Lines.AddObject(S, TLine.Create(0, F));
                Inc(F)
              End;
            FL := TStringList.Create;
            FL.Assign(Lines);
            Files.AddObject(Asterisk+ParamStr(ParamNameNum), FL);

            CloseFile(Inp);

            ProgGPU := TStringList.Create;
            ProgGPU.Add('#define __GPU__');
            ProgGPU.Add('');
            ProgGPU.Add('#define plan_vector_size() get_global_size(0)');
  	    ProgGPU.Add('#define plan_vector_id() get_global_id(0)');
            ProgGPU.Add('#define vector_max_size(S) get_global_size(0)');
            ProgGPU.Add('#define vector_max_units(S) (0)');
            ProgGPU.Add('#define get_device_id(n) ((char *)0)');
            ProgGPU.Add('');

            IsVectorized := False;
            IsClustered := False;
            SetLength(Restrictions, 0);
            Defines.AddObject('__REENT__', TObject(NewStr('1')));

            PatternsOrder.Clear;
            PatternsMode := pmNone;

            PreprocStage1(FollowDefs, Defines, ProgGPU, IsClustered, IsVectorized, Restrictions);

            PreprocStage1a(Restrictions);

            If L.Error Then
               Begin
                 WriteLn('Parse error',TLine(Lines.Objects[LCounter-2]).GetDescription);
                 Halt(-1)
               End;

            PreprocStage2(Restrictions);

            If L.Error Then
               Begin
                 WriteLn('Parse error',TLine(Lines.Objects[LCounter-2]).GetDescription);
                 Halt(-1)
               End;
            Inc(PassCount)
          Until PassCount >= PreprocPasses;

          // Insert Prolog code
          If Not ExtensionsOnly Then
             Begin
               WriteLn(Out, '#define __REENT__');
               WriteProlog(Out, IsClustered, IsVectorized);

               WriteString(Out, '__gpu_common', ProgGPU)
             End;

          // Restore primary lines from file (not from results of macromodules apply)
          CommentFlag := False;
          For F := 0 To Lines.Count-1 Do
            If Not TLine(Lines.Objects[F]).IsMacroResult Then
               Begin
                 S := TLine(Lines.Objects[F]).GetOriginalLine;
                 StripComments(S, CommentFlag);
                 Lines.Strings[F] := S;
               End;

          Declared:=TStringList.Create;
          Declared.CaseSensitive := True;
          TypeMaps:=TStringList.Create;
          TypeMaps.CaseSensitive := True;
          Reducts:=TStringList.Create;
          Reducts.CaseSensitive := True;
          LocGlobs:=TStringList.Create;
          LocGlobs.CaseSensitive := True;
          _Names:=TStringList.Create;
          _Names.CaseSensitive := True;
          Substs:=TStringList.Create;
          Substs.CaseSensitive := True;
          ChainSubsts:=TStringList.Create;
          ChainSubsts.CaseSensitive := True;
          Chain:=TStringList.Create;
          Chain.CaseSensitive := True;
          ChainNames:=TStringList.Create;
          ChainNames.CaseSensitive := True;
          TaskDependsList:=TStringList.Create;
          TaskDependsList.CaseSensitive := True;
          DeclarationList:=TStringList.Create;
          DeclarationList.CaseSensitive := True;
          // DeclarationList.Sorted:=True;
          IDList:=TStringList.Create;
          IDList.CaseSensitive := True;
          // IDList.Sorted:=True;
          Topology:=TStringList.Create;
          Topology.CaseSensitive := True;
          ReadFunction := False;
          FunctionText := '';
          SoftFunctionText := '';
          GPUFunctionText := '';
          FunctionThrowParams := '';
          FunctionType := '';
          FunctionID := '';
          FunctionParamNames := '';
          FirstBracketIsRead := False;
          ReadFunctionLevel := 0;
          AutosInserted := True;
          PureAutos := '';
          PureDummies := '';
          PlanAutos := '';
          gpuInit := '';

          ClusteredArrID := '';

          CommentFlag := False;
          LCounter:=1;
          While Not ((LCounter > Lines.Count) Or L.Error) Do
            Begin
              // Bypass the module's definitions
              If TLine(Lines.Objects[LCounter-1]).Restricted Then
                 Begin
                   Inc(LCounter);
                   Continue
                 End;
              Flag := True;
              S := Lines.Strings[LCounter-1];
              If Not NoSourceLines Then
                 Write(Out, TLine(Lines.Objects[LCounter-1]).GetLineNumbers);
              StripComments(S, CommentFlag);
              L.AnlzLine := S;
              If L.IsNextSet([Pound]) Then // #...
                 begin
                   F:=Length(S)-Length(L.AnlzLine);
                   L.Check(Pound);
                   ID:=L.GetIdent(True);
                   If ID=idPragma Then
                      begin
                        ID:=L.GetIdent(True);
                        If ID=idOmp Then
                           begin
                             ID:=L.GetIdent(True);
                             If ID=idParallel Then
                                ID:=L.GetIdent(True);
                             If ID=idPlan Then
                                begin
                                  ID:=L.GetIdent(True);
                                  S:=StringOfChar(' ',F);
                                  If ID=idFirst Then
                                     S:=S+'plan_group_first;'
                                  Else If ID=idLast Then
                                     S:=S+'plan_group_last;'
                                  Else If ID=idParallelize Then
                                     S:=S+'plan_group_parallelize;'
                                  Else
                                     Begin
                                       L.MakeError('''#pragma'' error: plan '+ID+' -- can''t understand...');
                                       Continue
                                     End
                                end
                           end
                      end;
                 end;
              If ReadFunction Then
                 begin
                   If (ReadFunctionLevel = 1) And Not AutosInserted Then
                      begin
                        FunctionText := FunctionText + CRLF + PureAutos + CRLF + S;
                        SoftFunctionText := SoftFunctionText + CRLF + PureAutos + CRLF + S;
                        GPUFunctionText := GPUFunctionText + CRLF + PureDummies + CRLF + gpuInit + CRLF + S;
                        WriteLn(Out, PlanAutos);
                        WriteLn(Out);
                        AutosInserted := True
                      end
                   Else
                      Begin
                        FunctionText := FunctionText + CRLF + S;
                        SoftFunctionText := SoftFunctionText + CRLF + S;
                        GPUFunctionText := GPUFunctionText + CRLF + S
                      End;
                   AnalyzeBrackets(FunctionID, S, FirstBracketIsRead, ReadFunctionLevel);
                   If FirstBracketIsRead And (ReadFunctionLevel = 0) Then
                      begin
                        FunctionText := FunctionText + CRLF;
                        SoftFunctionText := SoftFunctionText + CRLF;
                        GPUFunctionText := GPUFunctionText + CRLF;
                        ReadFunction := False;
                        FirstBracketIsRead := False;
                        ReadFunctionLevel := 0
                      end
                 end;
              L.AnlzLine:=S;
              ID:=L.FindIdent(True);
              If ID = idclustered Then
                 Begin
                   L.CheckIdent(idclustered, True);
                   L.Check(LeftBracket);
                   ID := L.GetIdent(False);
                   If (Length(ID) = 0) Or (ID = idnull) Then
                      ClusteredArrID := ''
                   Else
                      Begin
                        L.Check(RightBracket);
                        ClusteredArrID := ID
                      End;
                   If L.Empty Or L.Error Then
                      Begin
                        Inc(LCounter);
                        Continue
                      End;
                   S:=L.AnlzLine;
                   ID:=L.FindIdent(True)
                 End;
              If ID = idplan_topology Then
                 Begin
                   L.CheckIdent(idplan_topology, True);
                   F := LCounter+1;
                   GetFBlock(L,[SemiColon],Topology);
                   If L.IsNext(Slash) Then
                      Begin
                        L.Check(Slash);
                        S:=L.GetBalancedListItem(False,[SemiColon]);
                      End
                   Else
                      S := '';
                   L.Check(SemiColon);
                   CreateTopology(Out, ClusteredArrID, Chain, Topology, S);
                   WriteLn(Out,';');
                   S:=L.AnlzLine;
                   ID:=L.FindIdent(True)
                 End
              Else If (ID = idplan_registered_barrier) Or (ID = idreent_registered_barrier) Then
                 Begin
                   L.GetIdent(True);
                   L.Check(LeftBracket);

                   WriteLn(Out,'#ifdef _OPENMP');
                   WriteLn(Out,'do {');

                   If ID = idreent_registered_barrier Then
                      Begin
                        WriteLn(Out,'  int topo = ', L.GetBalancedListItem(False,[Comma]), ';');
                        L.Check(Comma)
                      End
                   Else
                      WriteLn(Out,'  int topo = plan_topology_num();');
                   S := ID;

                   ID := L.GetIdent(False);
                   L.Check(RightBracket);

                   WriteLn(Out,'  plan_set_lock(__topo_lock__);');
                   WriteLn(Out,'  __Topology * top = __TopologyStack[topo];');
                   WriteLn(Out,'  map<string,__Group *>::iterator itGroups = top->Groups.find("'+ID+'");');
                   WriteLn(Out,'  if (itGroups == top->Groups.end()) {');
                   WriteLn(Out,'     cout<<"Group '''+ID+''' does not exist in the current topology"<<endl;');
                   WriteLn(Out,'     exit(-1);');
                   WriteLn(Out,'  }');
                   WriteLn(Out,'  __Group * group = itGroups->second;');
                   WriteLn(Out,'  __Address_union A;');
                   WriteLn(Out,'  A.ref_idx.ref = (unsigned long long)&_call_'+FunctionID+' & 0xFFFFFFFF;');

                   If S = idreent_registered_barrier Then
                      WriteLn(Out,'  int num = reent_linear_num();')
                   Else
                      WriteLn(Out,'  int num = plan_linear_num();');

                   WriteLn(Out,'  A.ref_idx.idx = num;');

                   WriteLn(Out,'  __Node * node = top->Nodes[A.single];');
                   WriteLn(Out,'  if (!group->find(node)) {');
                   WriteLn(Out,'     cout<<"Barrier at "<<reinterpret_cast<void *>(&_call_'+FunctionID+')<<"["<<num<<"]: not registered in group ''"<<"'+ID+'"<<"''"<<endl;');
                   WriteLn(Out,'     exit(-1);');
                   WriteLn(Out,'  }');
                   WriteLn(Out,'#ifdef __REENT_MPI__');
                   WriteLn(Out,'  if (top->clustered) {');
                   WriteLn(Out,'     const char * GroupID = "'+ID+'";');
                   WriteLn(Out,'     __group_struct gs;');
                   WriteLn(Out,'     memmove(gs.group, GroupID, strlen(GroupID)+1);');
                   WriteLn(Out,'     gs.command = gcBarrier;');
                   WriteLn(Out,'');
                   WriteLn(Out,'     map<unsigned long long,__Node *>::iterator itNodes;');
                   WriteLn(Out,'     for (itNodes = top->Nodes.begin(); itNodes != top->Nodes.end(); itNodes++)');
                   WriteLn(Out,'         if (itNodes->second == node)');
                   WriteLn(Out,'            itNodes->second->barriered = group;');
                   WriteLn(Out,'         else if (group->find(itNodes->second))');
                   WriteLn(Out,'            MPI_Send(&gs, sizeof(gs), MPI_BYTE, itNodes->second->id, 1236, MPI_COMM_WORLD);');
                   WriteLn(Out,'     bool passed;');
                   WriteLn(Out,'     do {');
                   WriteLn(Out,'         plan_unset_lock(__topo_lock__);');
                   WriteLn(Out,'         _Yield();');
                   WriteLn(Out,'         plan_set_lock(__topo_lock__);');
                   WriteLn(Out,'         top->process_group_messages();');
                   WriteLn(Out,'         passed = true;');
                   WriteLn(Out,'         for (itNodes = top->Nodes.begin(); passed && itNodes != top->Nodes.end(); itNodes++)');
                   WriteLn(Out,'             if (group->find(itNodes->second))');
                   WriteLn(Out,'                if (itNodes->second->barriered != group)');
                   WriteLn(Out,'                   passed = false;');
                   WriteLn(Out,'     } while (!passed);');
                   WriteLn(Out,'     for (itNodes = top->Nodes.begin(); itNodes != top->Nodes.end(); itNodes++)');
                   WriteLn(Out,'         if (group->find(itNodes->second))');
                   WriteLn(Out,'            itNodes->second->barriered = NULL;');
                   WriteLn(Out,'     plan_unset_lock(__topo_lock__);');
                   WriteLn(Out,'  } else {');
                   WriteLn(Out,'#endif');
                   WriteLn(Out,'    plan_unset_lock(__topo_lock__);');
                   WriteLn(Out,'    #pragma omp critical(__'+ID+'1)');
                   WriteLn(Out,'    {');
                   WriteLn(Out,'      group->enter_barrier();');
                   WriteLn(Out,'    }');
                   WriteLn(Out,'    #pragma omp critical(__'+ID+'2)');
                   WriteLn(Out,'    {');
                   WriteLn(Out,'      group->wait_barrier();');
                   WriteLn(Out,'    }');
                   WriteLn(Out,'    group->leave_barrier();');
                   WriteLn(Out,'#ifdef __REENT_MPI__');
                   WriteLn(Out,'  }');
                   WriteLn(Out,'#endif');
                   WriteLn(Out,'} while(0)');
                   WriteLn(Out,'#else');
                   WriteLn(Out,'while(0)');
                   WriteLn(Out,'#endif');
                   S:=L.AnlzLine;
                   ID:=L.FindIdent(True)
                 End
              Else If ID = idplan_critical Then
                 Begin
                   L.CheckIdent(idplan_critical, True);
                   L.Check(LeftBracket);
                   ID := L.GetIdent(False);
                   If Length(ID) = 0 Then
                      L.Expect('Critical section identifier without quotes')
                   Else
                      Begin
                        L.Check(RightBracket);
                        WriteLn(Out,'#pragma omp critical('+ID+')')
                      End;
                   S:=L.AnlzLine;
                   ID:=L.FindIdent(True)
                 End;

              If Not ((ID=idReenterable) Or (ID=idChain)) Then
                 Begin // Isn't declaration
                   HandleChains(Out, L, L1, S, ClusteredArrID, Chain);
                   If L.Error Then Continue;

                   HandleProcMentions(L, L1, Declared, S);
                   If L.Error Then Continue
                 End;

              HandleContinues(L, S);
              If L.Error Then Continue;

              HandlePlansThrows(L, S);
              If L.Error Then Continue;

              L.AnlzLine:=S;
              IsMarkup:=L.IsNextIdent(idMarkupdef, True);
              If IsMarkup Or L.IsNextIdent(idTypedef, True) Then
                Begin
                  L.GetIdent(True);
                  If IsMarkup Then
                     S:='typedef '+L.AnlzLine; // Will be an imaginary type to simplify parsing
                  S1:=L.GetIdent(True);
                  If (S1 = idUnion) Or (S1 = idStruct) Then
                     Begin
                       TagID := '';
                       S1:=AnalyzeType(L,IsMarkup,TagID,S);
                       TypeMaps.Values[L.GetBefore(True,[SemiColon])]:=S1;
                       If Length(TagID)<>0 Then
                          TypeMaps.Values[TagID]:=S1
                     End;
                  WriteLn(Out,S)
                End
              Else
                begin
                  ID:=L.GetIdent(True);
                  ChainMode:= ID=idChain;
                  If ChainMode Or (ID=idReenterable) Then
                     begin
                       If L.IsNextSet([LeftSqrBracket]) Then
                          Begin
                            Ldecl:='circular_list';
                            LFlag:=dcCirc;
                            Lfmt:=L.GetString(LeftSqrBracket,RightSqrBracket);
                            Lparm:='('+Lfmt+', _n%s, (int *)_s%s, (int *)_o%s)';
                            Lfmt:='(1, %s)'
                          End
                       Else
                          Begin
                            Ldecl:='reent_list';
                            LFlag:=dcList;
                            Lparm:='(_n%s, (int *)_s%s, (int *)_o%s)';
                            Lfmt:='(1, %s)'
                          End;
                       If L.IsNextIdent(idStatic, True) And Not ChainMode Then
                          Begin
                            L.GetIdent(True);
                            StaticFlag:=smStatic;
                            If L.IsNextIdent(idGlobal, True) Then
                               L.CheckIdent(idGlobal, True)
                            Else If L.IsNextIdent(idLocal, True) Then
                               Begin
                                 StaticFlag:=smKept;
                                 L.CheckIdent(idLocal, True)
                               End
                          End
                       Else
                          StaticFlag:=smDynamic;
                       TypeID := 'void';
                       ID:=L.GetBefore(True,[Space, Tabulation, LeftBracket]);
                       L.DelSpaces;
                       If Not L.IsNext(LeftBracket) Then
                          begin
                            If ChainMode Then
                               begin
                                 WriteLn('Chain procedures can''t be a functions',TLine(Lines.Objects[LCounter-1]).GetDescription);
                                 Halt;
                               end;
                            If StaticFlag<>smDynamic Then
                               begin
                                 WriteLn('Static procedures can''t be a functions',TLine(Lines.Objects[LCounter-1]).GetDescription);
                                 Halt;
                               end;
                            TypeID := ID;
                            Repeat
                              ID:=L.GetBefore(True,[Space, Tabulation, LeftBracket]);
                              L.DelSpaces;
                              If Not L.IsNext(LeftBracket) Then
                                 TypeID := TypeID + ' ' + ID
                            Until L.IsNext(LeftBracket);
                          end;
                       FunctionID := ID;
                       FunctionType := TypeID;
                       L.Check(LeftBracket);
                       InputProcName:='';
                       PrmDeclaration := '';
                       RefsDeclaration := '';
                       RedDummies := ''; RedModifs := ''; ResetDummies := '';
                       pRedDummies := ''; pRedModifs := ''; pRedModifs_ := '';
                       _RedDummies := ''; _pRedDummies := ''; _RedModifs := '';
                       TypeTaskID := ''; NameTaskID := ''; TaskEmpty := '';
                       gpuParams := '';
                       Params:=CollectParamsAfterBracket(L,_Names,Substs,PrmDeclaration,RefsDeclaration,Reducts,
                                                         RedDummies,RedModifs,
                                                         _RedDummies,ResetDummies,_RedModifs,
                                                         _pRedDummies,pRedDummies,pRedModifs,pRedModifs_,
                                                         TypeTaskID, NameTaskID, TaskEmpty,
                                                         InputProcName,
                                                         gpuParams, gpuInit,
                                                         TypeMaps,
                                                         LocGlobs);
                       S1 := L.AnlzLine;
                       F := Pos(LeftFBracket, S1);
                       If F = 0 Then
                          begin
                             FunctionText := FunctionType + ' __atomic_' + ID + '$$$ __transaction_atomic';
                             SoftFunctionText := FunctionType + ' __soft_atomic_' + ID + '$$$ ';
                             GPUFunctionText := '__kernel ' + FunctionType + ' gpu_' + ID + '$$$';
                             FirstBracketIsRead := False;
                             ReadFunctionLevel := 0
                          end
                       Else
                          begin
                            FunctionText := FunctionType + ' __atomic_' + ID + '$$$ __transaction_atomic {';
                            SoftFunctionText := FunctionType + ' __soft_atomic_' + ID + '$$$ {';
                            GPUFunctionText := '__kernel ' + FunctionType + ' gpu_' + ID + '$$$ {';
                            FirstBracketIsRead := True;
                            ReadFunctionLevel := 1
                          end;
                       If Not L.Error Then
                          begin
                            S2 := Params;
                            If Length(S2) > 0 Then
                               If S2[1] = ',' Then S2[1] := '('
                               Else S2 := '(' + S2
                            Else
                               S2 := '()';
                            FunctionText := StringReplace(FunctionText, '$$$', S2, [rfReplaceAll]);
                            SoftFunctionText := StringReplace(SoftFunctionText, '$$$', S2, [rfReplaceAll]);
                            GPUFunctionText := StringReplace(GPUFunctionText, '$$$', '('+gpuParams+')', [rfReplaceAll]);
                            S2 := StringReplace(FunctionText, '__transaction_atomic', '', [rfReplaceAll]);
                            If S2[Length(S2)] = LeftFBracket Then
                               WriteLn(Out, Copy(S2, 1, Length(S2)-1), ';')
                            Else
                               WriteLn(Out, S2, ';');
                            S2 := SoftFunctionText;
                            If S2[Length(S2)] = LeftFBracket Then
                               WriteLn(Out, Copy(S2, 1, Length(S2)-1), ';')
                            Else
                               WriteLn(Out, S2, ';');
                            If IsVectorized Then
                               Begin
                                 WriteLn(Out,'#ifdef __REENT_GPU__');
                                 WriteLn(Out,'extern const char * gpu_'+ID+'[];');
                                 WriteLn(Out,'#endif')
                               End;
                            eRedDummies:=StringReplace(RedDummies,CRLF,' \'+CRLF,[rfReplaceAll]);
                            eRedModifs:=StringReplace(RedModifs,CRLF,' \'+CRLF,[rfReplaceAll]);
                            _eRedDummies:=StringReplace(_RedDummies,CRLF,' \'+CRLF,[rfReplaceAll]);
                            ResetDummies:=StringReplace(ResetDummies,CRLF,' \'+CRLF,[rfReplaceAll]);
                            _eRedModifs:=StringReplace(_RedModifs,CRLF,' \'+CRLF,[rfReplaceAll]);
                            PrmStruct:='_params_'+ID;
                            ThrStruct:='_throw_'+ID;
                            ParamDummy:='_dummy_'+ID+'__LOC__';
                            rParamNames:='';
                            _rParamNames := '';
                            ParamNames:='';
                            _ParamNames := '';
                            ParamAsgns:='';
                            GetAsgns:='';
                            ParamReasgns:='';
                            STParamReasgns:='';
                            rParamDummies:='';
                            ParamDummies:='';
                            With _Names Do
                              For F:=0 To Count-1 Do
                                Begin
                                  If Reducts.Strings[F]<>'' Then
                                     begin
                                       rS1:=redVarPrefix;
                                       _rParamNames:=_rParamNames+rS1+Strings[F]+',';
                                     end
                                  Else
                                     begin
                                       rS1:='';
                                       _rParamNames:=_rParamNames+tran(_Names,Substs,Strings[F])+','
                                     end;
                                  rParamNames:=rParamNames+rS1+Strings[F]+',';
                                  ParamNames:=ParamNames+Strings[F]+',';
                                  _ParamNames:=_ParamNames+tran(_Names,Substs,Strings[F])+',';
                                  ParamAsgns:=ParamAsgns+' '+ParamDummy+'.'+Strings[F]+'='+tran(_Names,Substs,Strings[F])+'; \';
                                  GetAsgns:=GetAsgns+' '+Strings[F]+'=__dummy_throw__.'+Strings[F]+';';
                                  CastedFlag:=Objects[F];
                                  If Flag Then
                                     Begin
                                       S1:=IntToStr(1 Shl (Count-F));
                                       ParamReasgns:=ParamReasgns+' if (('+ParamDummy+'.Flags & '+S1+') || *__continue_plan__==2) '+rS1+Strings[F]+'='+ParamDummy+'.'+Strings[F]+'; \'+#$0D#$0A;
                                       STParamReasgns:=STParamReasgns+' if ((_dummy_.Flags & '+S1+') || *__continue_plan__==2) '+rS1+Strings[F]+'=_dummy_.'+Strings[F]+'; \'+#$0D#$0A;
                                       ParamDummies:=ParamDummies+','+Strings[F];
                                       rParamDummies:=rParamDummies+','+rS1+Strings[F]
                                     End
                                  Else
                                     Begin
                                       ParamDummies:=ParamDummies+',##.'+Strings[F];
                                       rParamDummies:=rParamDummies+',##.'+rS1+Strings[F]
                                     End;
                                  If F<Count-1 Then
                                     Begin
                                       ParamAsgns:=ParamAsgns+CRLF;
                                       GetAsgns:=GetAsgns+CRLF
                                     End
                                End;
                            FunctionParamNames := ParamNames;
                            ParamDummies:=',__nprocs__'+ParamDummies;
                            rParamDummies:=',__nprocs__'+rParamDummies;
                            STParamDummies:=StringReplace(rParamDummies,'##','_dummy_',[rfReplaceAll]);
                            SoftSTParamDummies:=StringReplace(ParamDummies,'##','_dummy_',[rfReplaceAll]);
                            ParamDummies:=StringReplace(ParamDummies,'##',ParamDummy,[rfReplaceAll]);
                            rParamDummies:=StringReplace(rParamDummies,'##',ParamDummy,[rfReplaceAll]);

                            Proc:='_call_'+ID;

                            oEvs:='_events_'+ID;
                            If ChainMode Then
                               Begin
                                 If L.IsNextIdent(idThrow, True) Then
                                    Begin
                                      L.GetIdent(True);
                                      If L.Check(LeftBracket) Then
                                         Begin
                                           L1.AnlzLine := L.AnlzLine;
                                           S := L1.GetBalancedListItem(True,[RightBracket]);
                                           If (Pos(Space, S) <> 0) Or (Pos(Tabulation, S) <> 0) Then
                                              Begin
                                                 ThrDeclaration := '';
                                                 CollectParamsAfterBracket(L,ChainNames,ChainSubsts,ThrDeclaration,S, Nil,
                                                                           S, S, S, S, S, S,
                                                                           S, S, S,
                                                                           S, S, S,
                                                                           InputProcName,
                                                                           S, S,
                                                                           Nil,
                                                                           Nil);
                                                 eRedDummies:=StringReplace(RedDummies,CRLF,' \'+CRLF,[rfReplaceAll]);
                                                 eRedModifs:=StringReplace(RedModifs,CRLF,' \'+CRLF,[rfReplaceAll]);
                                                 _eRedDummies:=StringReplace(_RedDummies,CRLF,' \'+CRLF,[rfReplaceAll]);
                                                 _eRedModifs:=StringReplace(_RedModifs,CRLF,' \'+CRLF,[rfReplaceAll]);
                                                 ThrDeclaration:=ThrDeclaration+CRLF+'}'
                                              End
                                           Else
                                              Begin
                                                WriteLn('Chain procedures can''t designate exceptions',TLine(Lines.Objects[LCounter-1]).GetDescription);
                                                Halt;
                                              End
                                         End
                                      Else
                                         Continue
                                    End
                                 Else
                                    Begin
                                      ThrDeclaration:='typedef _params_'+ID;
                                      ChainNames.Assign(_Names);
                                      ChainSubsts.Assign(Substs)
                                    End;
                                 ThrParamNames:='';
                                 _ThrParamNames:='';
                                 ThrParamAsgns:='';
                                 With ChainNames Do
                                   For F:=0 To Count-1 Do
                                     Begin
                                       ThrParamNames:=ThrParamNames+Strings[F]+',';
                                       _ThrParamNames:=_ThrParamNames+tran(ChainNames,ChainSubsts,Strings[F])+',';
                                       If Strings[F] = InputProcName Then
                                          ThrParamAsgns:=' '+ThrParamAsgns+'__dummy_throw__.'+Strings[F]+'='+'((((unsigned long long)&'+Proc+')<<32)+plan_linear_num())'+'; \'
                                       Else
                                          ThrParamAsgns:=' '+ThrParamAsgns+'__dummy_throw__.'+Strings[F]+'='+tran(ChainNames,ChainSubsts,Strings[F])+'; \';
                                       If F<Count-1 Then
                                          ThrParamAsgns:=ThrParamAsgns+CRLF
                                     End
                               End;
                            TaskIf:='';
                            TaskSet:='';
                            TaskReset:='';
                            d_eli:='';
                            TaskDependsList.Clear;
                            S2:='';
                            If Length(NameTaskID)=0 Then
                               Begin
                                 If Not (L.Empty Or L.IsNextSet([LeftFBracket,SemiColon])) Then
                                    L.MakeError('{ or end of line was expected but the following sequence was found: '+L.AnlzLine)
                               End
                            Else
                               Begin
                                 While Not (L.Empty Or L.Error Or L.IsNextSet([LeftFBracket,SemiColon])) Do
                                   If Not CheckOneArgPredicate(S2,L,[TypeTaskID],['id'],ID,'char',idIf,'1','&=','$$',TaskIf) Then
                                   If Not CheckOneArgPredicate(S2,L,[TypeTaskID],['id'],ID,'void',idSet,'','','$$',TaskSet) Then
                                   If Not CheckOneArgPredicate(S2,L,[TypeTaskID],['id'],ID,'void',idReset,'','','$$',TaskReset) Then
                                   If Not CheckOneArgPredicate(S2,L,[TypeTaskID],['id'],ID,'',idDepends,'','','$$',d_eli) Then
                                      L.MakeError('Unknown sequence: '+L.AnlzLine);
                                 If Length(d_eli)<>0 Then
                                    Begin
                                      L1.AnlzLine:=d_eli + Comma;
                                      d_eli:=L.AnlzLine;
                                      If Length(TaskEmpty)<>0 Then
                                         S1:='$$==('+TaskEmpty+')||'
                                      Else
                                         S1:='';
                                      While Not (L1.Empty Or L1.Error) Do
                                        Begin
                                          L.AnlzLine:='DEP('+L1.GetBalancedListItem(True,[Comma])+')';
                                          If CheckOneArgPredicate(S2,L,['map<'+TypeTaskID+',char> *',TypeTaskID],['use_ids','id'],ID,'char','DEP','1',
                                             '&=',S1+'use_ids->find($$)==use_ids->end()',S) Then
                                             TaskDependsList.Add(S)
                                        End;
                                      L.AnlzLine:=d_eli;
                                      d_eli:='Banzai!!!'
                                    End
                               End;
                            // Chain interface... if not presents -- equal to main interface...
                            IsDeclaration:=L.IsNext(SemiColon);
                            ReadFunction := Not IsDeclaration;
                            AutosInserted := Not ReadFunction;
                            If Not ReadFunction Then
                               begin
                                 FunctionText := '';
                                 SoftFunctionText := '';
                                 GPUFunctionText := '';
                                 FunctionParamNames := '';
                                 FunctionThrowParams := '';
                                 ReadFunctionLevel := 0;
                                 FirstBracketIsRead := False
                               end
                            Else
                               begin
                                 NMParams := StringReplace(Params, '&', ' ', [rfReplaceAll]);
                                 If Length(NMParams) <= 2 Then
                                    GlueSymbol := ''
                                 Else
                                    GlueSymbol := ',';
                                 PlanAutos :=
                                          'auto _plan_empty = [&] ()->int {' + CRLF +
                                          '  __plan_locking__;'+CRLF+
                                          '  int result = __event_list__->empty();'+CRLF+
                                          '  __plan_unlocking__;'+CRLF+
                                          '  return result;' + CRLF +
                                          '};' + CRLF +
                                          'auto plan_first = [&] (' + Copy(NMParams, 2, Length(NMParams)-2) + GlueSymbol + ' int __mask__)->int {' + CRLF +
                                          '  _plan_first(' + FunctionParamNames + '__mask__);'+CRLF+
                                          '  return 1;' + CRLF +
                                          '};' + CRLF +
                                          'auto plan_last = [&] (' + Copy(NMParams, 2, Length(NMParams)-2) + GlueSymbol + ' int __mask__)->int {' + CRLF +
                                          '  _plan_last(' + FunctionParamNames + '__mask__);'+CRLF+
                                          '  return 1;' + CRLF +
                                          '};' + CRLF +
                                          'auto plan_get_first = [&] (' + RefsDeclaration + ')->int {' + CRLF +
                                          '  int result = 1;'+CRLF+
                                          '#if !defined(__REENT_MPI__) && !defined(_OPENMP)'+CRLF+
                                          '  if (plan_empty) return 2;'+CRLF+
                                          '#endif'+CRLF+
                                          '  __get_item_begin__(' + ID + ', front);'+CRLF+
                                             GetAsgns+CRLF+
                                          '  __get_item_end__;'+CRLF+
                                          '  return result;' + CRLF +
                                          '};' + CRLF +
                                          'auto plan_get_last = [&] (' + RefsDeclaration + ')->int {' + CRLF +
                                          '  int result = 1;'+CRLF+
                                          '#if !defined(__REENT_MPI__) && !defined(_OPENMP)'+CRLF+
                                          '  if (plan_empty) return 2;'+CRLF+
                                          '#endif'+CRLF+
                                          '  __get_item_begin__(' + ID + ', back);'+CRLF+
                                             GetAsgns+CRLF+
                                          '  __get_item_end__;'+CRLF+
                                          '  return result;' + CRLF +
                                          '};' + CRLF +
                                          'auto _plan_stop = [&] ()->int {' + CRLF +
                                          '  m_plan_stop;'+CRLF+
                                          '  return 1;' + CRLF +
                                          '};' + CRLF +
                                          'auto _plan_group_first = [&] ()->int {' + CRLF +
                                          '  m_plan_group_first;'+CRLF+
                                          '  return 1;' + CRLF +
                                          '};' + CRLF +
                                          'auto _plan_group_last = [&] ()->int {' + CRLF +
                                          '  m_plan_group_last;'+CRLF+
                                          '  return 1;' + CRLF +
                                          '};' + CRLF +
                                          'auto _plan_group_parallelize = [&] ()->int {' + CRLF +
                                          '  m_plan_group_parallelize;'+CRLF+
                                          '  return 1;' + CRLF +
                                          '};' + CRLF +
                                          'auto _plan_group_atomize = [&] ()->int {' + CRLF +
                                          '  m_plan_group_atomize;'+CRLF+
                                          '  return 1;' + CRLF +
                                          '};' + CRLF +
                                          'auto _plan_group_soft_atomize = [&] ()->int {' + CRLF +
                                          '  __plan_locking__;'+CRLF+
                                          '  int __n__ = 0;'+CRLF+
                                          '  int __max__ = omp_get_max_threads();'+CRLF+
                                          '  '+Ldecl+'<_params_'+ID+'>::iterator it;'+CRLF+
                                          '  for (it = __event_list__->begin(); __n__ < __max__ && it != __event_list__->end() && !((*it).Flags & 1); ++it)'+CRLF+
                                          '      __n__++;'+CRLF+
                                          '  if (__n__ == 0) return 1;'+CRLF+
                                          '  if (__n__ == __max__ && it != __event_list__->end() && !((*it).Flags & 1)) {'+CRLF+
                                          '     cout<<"Error: too many items in soft atomiized section of plan: exceeds "<<__max__<<endl;'+CRLF+
                                          '     exit(-1);'+CRLF+
                                          '  }'+CRLF+
                                          '  it = __event_list__->begin();'+CRLF+
                                          '  plan_item_type(' + ID + ') * __data__ = new plan_item_type(' + ID + ')[__n__];'+CRLF+
                                          '  for (int j = 0; j < __n__; j++) {'+CRLF+
                                          '      __data__[j] = *it; ++it;'+CRLF+
                                          '  }'+CRLF+
                                          '  #pragma omp parallel num_threads(__n__)'+CRLF+
                                          '  {'+CRLF+
                                          '     int __id__ = omp_get_thread_num();'+CRLF+
                                          '     plan_item_type(' + ID + ') & _dummy_ = __data__[__id__];'+CRLF+
                                          '     transaction_atomic("") {'+CRLF+
                                          '        __soft_atomic_' + ID + '(' + Copy(SoftSTParamDummies, 13 {eliminate ',__nprocs__,'}, Length(SoftSTParamDummies)-1) + ');'+CRLF+
                                          '     }'+CRLF+
                                          '  }'+CRLF+
                                          '  delete[] __data__;'+CRLF+
                                          '  for (int i = 0; i < __n__; i++) {'+CRLF+
                                          '      __event_list__->pop_front();'+CRLF+
                                          '  }'+CRLF+
                                          '  if (!__event_list__->empty()) {'+CRLF+
                                          '     plan_item_type(' + ID + ') & __planned__ = __event_list__->front();'+CRLF+
                                          '     if (__planned__.Flags & 1) __event_list__->pop_front();'+CRLF+
                                          '  }'+CRLF+
                                          '  __plan_unlocking__;'+CRLF+
                                          '  return 1;' + CRLF +
                                          '};' + CRLF +
                                          'auto _plan_group_vectorize = [&] (const char * Device)->int {' + CRLF +
                                          '  m_plan_group_vectorize(Device);'+CRLF+
                                          '  return 1;' + CRLF +
                                          '};' + CRLF +
                                          'auto _clear_plan = [&] ()->int {' + CRLF +
                                          '  m_clear_plan;'+CRLF+
                                          '  return 1;' + CRLF +
                                          '};' + CRLF +
                                          '__dummy_counter += '+IntToStr(CRC(ID))+'; /* Some magic to ensure that functions are different (our answer to the clever compiler) and their addresses are different too */';
                                 PureAutos :=
                                          'auto plan_first = [&] (' + Copy(NMParams, 2, Length(NMParams)-1) + '->int {' + CRLF +
                                          '  _plan_first(' + Copy(FunctionParamNames,1,Length(FunctionParamNames)-1) + ');'+CRLF+
                                          '  return 1;' + CRLF +
                                          '};' + CRLF +
                                          'auto plan_last = [&] (' + Copy(NMParams, 2, Length(NMParams)-1) + '->int {' + CRLF +
                                          '  _plan_last(' + Copy(FunctionParamNames,1,Length(FunctionParamNames)-1) + ');'+CRLF+
                                          '  return 1;' + CRLF +
                                          '};' + CRLF +
                                          'auto plan_get_first = [&] (' + RefsDeclaration + ')->int {' + CRLF +
                                          '  // Can''t be executed'+CRLF+
                                          '  return 1;' + CRLF +
                                          '};' + CRLF +
                                          'auto plan_get_last = [&] (' + RefsDeclaration + ')->int {' + CRLF +
                                          '  // Can''t be executed'+CRLF+
                                          '  return 1;' + CRLF +
                                          '};' + CRLF +
                                          'auto _plan_stop = [&] ()->int {' + CRLF +
                                          '  m_plan_stop;'+CRLF+
                                          '  return 1;' + CRLF +
                                          '};' + CRLF +
                                          'auto _plan_group_first = [&] ()->int {' + CRLF +
                                          '  m_plan_group_first;'+CRLF+
                                          '  return 1;' + CRLF +
                                          '};' + CRLF +
                                          'auto _plan_group_last = [&] ()->int {' + CRLF +
                                          '  m_plan_group_last;'+CRLF+
                                          '  return 1;' + CRLF +
                                          '};' + CRLF +
                                          'auto _plan_group_parallelize = [&] ()->int {' + CRLF +
                                          '  m_plan_group_parallelize;'+CRLF+
                                          '  return 1;' + CRLF +
                                          '};' + CRLF +
                                          'auto _plan_group_atomize = [&] ()->int {' + CRLF +
                                          '  m_plan_group_atomize;'+CRLF+
                                          '  return 1;' + CRLF +
                                          '};' + CRLF +
                                          'auto _plan_group_soft_atomize = [&] ()->int {' + CRLF +
                                          '  m_plan_group_soft_atomize;'+CRLF+
                                          '  return 1;' + CRLF +
                                          '};' + CRLF +
                                          'auto _plan_group_vectorize = [&] (const char * Device)->int {' + CRLF +
                                          '  m_plan_group_vectorize(Device);'+CRLF+
                                          '  return 1;' + CRLF +
                                          '};' + CRLF +
                                          'auto _clear_plan = [&] ()->int {' + CRLF +
                                          '  m_clear_plan;'+CRLF+
                                          '  return 1;' + CRLF +
                                          '};' + CRLF +
                                          '__dummy_counter += '+IntToStr(CRC(ID))+'; /* Some magic to ensure that functions are different (our answer to the clever compiler) and their addresses are different too */';
                                 PureDummies :=
                                          '#define plan_empty 1' + CRLF +
                                          '#define plan_first(' + Copy(FunctionParamNames,1,Length(FunctionParamNames)-1) + ') 1'+CRLF+
                                          '#define plan_last(' + Copy(FunctionParamNames,1,Length(FunctionParamNames)-1) + ') 1'+CRLF+
                                          '#define plan_get_first(' + Copy(FunctionParamNames,1,Length(FunctionParamNames)-1) + ') 1'+CRLF+
                                          '#define plan_get_last(' + Copy(FunctionParamNames,1,Length(FunctionParamNames)-1) + ') 1'+CRLF+
                                          '#define plan_stop 1' + CRLF +
                                          '#define plan_group_first 1' + CRLF +
                                          '#define plan_group_last 1' + CRLF +
                                          '#define plan_group_parallelize 1' + CRLF +
                                          '#define plan_group_atomize 1' + CRLF +
                                          '#define plan_group_soft_atomize 1' + CRLF +
                                          '#define plan_group_vectorize(S) 1' + CRLF +
                                          '#define throw_num_stages() 1' + CRLF +
                                          '#define throw_stage() 0' + CRLF +
                                          '#define clear_plan 1' + CRLF
                               end;
                            If Declared.IndexOf(ID)<0 Then
                               Begin
                                 RealType:=WriteStructDeclaration(Out,IDList,DeclarationList, PrmDeclaration+CRLF+'}', PrmStruct);
                                 With _Names Do
                                   Begin
                                     WriteLn(Out, PrmStruct, ' _x', PrmStruct,';');
                                     WriteLn(Out, 'int _n', PrmStruct, ' = ', Count, ';');
                                     Write(Out, 'int _s', PrmStruct, '[] = {');
                                     For F := 0 To Count-1 Do
                                       Write(Out, 'sizeof(_x'+PrmStruct+'.'+Strings[F]+'),');
                                     WriteLn(Out, '0};');
                                     Write(Out, 'int _o', PrmStruct, '[] = {');
                                     For F := 0 To Count-1 Do
                                       Write(Out, '((char *)&_x'+PrmStruct+'.'+Strings[F]+')-((char *)&_x'+PrmStruct+'),');
                                     WriteLn(Out, '0};')
                                   End;
                                 If ChainMode Then
                                    WriteStructDeclaration(Out,IDList,DeclarationList, ThrDeclaration, ThrStruct);
                                 Declared.Add(ID);
                                 If ChainMode Then
                                    Chain.AddObject(ID,TObject(NewStr(Ldecl+#0+Format(Lparm,[PrmStruct, PrmStruct, PrmStruct]))));
                                 If StaticFlag<>smDynamic Then
                                    Begin
                                      Evs:=oEvs;
                                      WriteLn(Out,'#define '+ID+'_plan_type '+Ldecl+'<'+PrmStruct+'>');
                                      Q:=IDList.IndexOf(RealType);
                                      K:=TObjectToInteger(IDList.Objects[Q]);
                                      If (K And LFlag) = 0  Then
                                         Begin
                                            IDList.Objects[Q] := IntegerToTObject(K Or LFlag);
                                            WriteLn(Out,'plan_type('+ID+') & operator <<(plan_type('+ID+') & A, const plan_item_type('+ID+') &Item) {');
                                            WriteLn(Out,' A.push_back(Item);');
                                            WriteLn(Out,' return A;');
                                            WriteLn(Out,'}');
                                            WriteLn(Out,'plan_type('+ID+') & operator >>(const plan_item_type('+ID+') &Item, plan_type('+ID+') &A) {');
                                            WriteLn(Out,' A.push_front(Item);');
                                            WriteLn(Out,' return A;');
                                            WriteLn(Out,'}');
                                            WriteLn(Out,'plan_type('+ID+') & operator <<(plan_item_type('+ID+') &Item, plan_type('+ID+') &A) {');
                                            WriteLn(Out,' Item = A.front();');
                                            WriteLn(Out,' A.pop_front();');
                                            WriteLn(Out,' return A;');
                                            WriteLn(Out,'}');
                                            WriteLn(Out,'plan_type('+ID+') & operator >>(plan_type('+ID+') &A, plan_item_type('+ID+') &Item) {');
                                            WriteLn(Out,' Item = A.back();');
                                            WriteLn(Out,' A.pop_back();');
                                            WriteLn(Out,' return A;');
                                            WriteLn(Out,'}');
                                            WriteLn(Out,'plan_item_type('+ID+') & operator ++(plan_type('+ID+') & A) {');
                                            WriteLn(Out,' return A.front();');
                                            WriteLn(Out,'}');
                                            WriteLn(Out,'plan_item_type('+ID+') & operator ++(plan_type('+ID+') & A, int) {');
                                            WriteLn(Out,' return A.back();');
                                            WriteLn(Out,'}')
                                         End;
                                      If StaticFlag=smStatic Then
                                         Begin
                                           WriteLn(Out,Ldecl+'<'+PrmStruct+'> '+Evs+' = '+Ldecl+'<'+PrmStruct+'>'+Format(Lparm,[PrmStruct, PrmStruct, PrmStruct])+';');
                                           WriteLn(Out,'#define '+ID+'_plan_prefix');
                                         End
                                      Else
                                         Begin
                                           WriteLn(Out,Ldecl+'<'+PrmStruct+'> * '+Evs+' = new '+Ldecl+'<'+PrmStruct+'>'+Format(Lparm,[PrmStruct, PrmStruct, PrmStruct])+';');
                                           WriteLn(Out,'#define '+ID+'_plan_prefix *');
                                           WriteLn(Out,'reent_list<'+Ldecl+'<'+PrmStruct+'> *> _'+Evs+' = reent_list<'+Ldecl+'<'+PrmStruct+'> *>'+Format(Lfmt,[Evs])+';');
                                           WriteLn(Out,'volatile int n_'+Evs+' = -1;');
                                           Evs:='(*'+Evs+')';
                                           oEvs:=Evs
                                         End
                                    End
                                 Else
                                    Evs:='_events_'+ID+'__LOC__';

                                 If ChainMode And Not IsDeclaration Then
                                    begin
                                      WriteThrowMacroses(Out,ID,_ThrParamNames);
                                      FunctionThrowParams := ThrParamNames
                                    end;
                                 If Not IsDeclaration Then
                                    WritePlanMacroses(Out,ID,_ParamNames, LocGlobs, _Names, Ldecl);
                                 If Length(S2)<>0 Then
                                    WriteLn(Out,S2);
                                 WriteLn(Out,'#ifdef _OPENMP');
                                 WriteLn(Out,'#define __plan_group_'+ID+'__(__Direction__) \');
                                 WriteLn(Out,'do { \');
                                 WriteLn(Out,' '+PrmStruct+' '+ParamDummy+'; \');
                                 WriteLn(Out,' '+ParamDummy+'.Flags=1; \');
                                 WriteLn(Out,' __plan_locking__; \');
                                 WriteLn(Out,' __event_list__->push_##__Direction__(_dummy_'+ID+'__LOC__); \');
                                 WriteLn(Out,' __plan_unlocking__; \');
                                 WriteLn(Out,' __plan_signal__; \');
                                 WriteLn(Out,'} while(0)');
                                 WriteLn(Out,'#else');
                                 WriteLn(Out,'#define __plan_group_'+ID+'__(__Direction__) while(0)');
                                 WriteLn(Out,'#endif');
                                 WriteLn(Out,'#define __plan_'+ID+'__(__Direction__,'+_ParamNames+'__mask__) \');
                                 WriteLn(Out,'do { \');
                                 WriteLn(Out,' '+PrmStruct+' '+ParamDummy+'; \');
                                 WriteLn(Out,' '+ParamDummy+'.Flags=__mask__<<1; \');
                                 If Length(TaskReset)<>0 Then
                                    Begin
                                      WriteLn(Out,' '+TypeTaskID+' id = '+NameTaskID+'; \');
                                      Write(Out,' ');
                                      If Length(TaskEmpty)<>0 Then
                                         Write(Out,'if (id!=('+TaskEmpty+')) ');
                                      WriteLn(Out,TaskReset+'; \')
                                    End;
                                 If Length(ParamAsgns)>0 Then
                                    WriteLn(Out,ParamAsgns);
                                 WriteLn(Out,' __plan_locking__; \');
                                 WriteLn(Out,' __event_list__->push_##__Direction__('+ParamDummy+'); \');
                                 WriteLn(Out,' __plan_unlocking__; \');
                                 WriteLn(Out,' __plan_signal__; \');
                                 WriteLn(Out,'} while(0)');
                                 If ChainMode Then
                                    Begin
                                      WriteLn(Out,'#define __throw_'+ID+'__(__Direction__,'+_ThrParamNames+'__mask__) \');
                                      WriteLn(Out,'do { \');
                                      WriteLn(Out,' _throw_'+ID+' __dummy_throw__; \');
                                      WriteLn(Out,' __dummy_throw__.Flags=__mask__<<1; \');
                                      If Length(ThrParamAsgns)>0 Then
                                         WriteLn(Out,ThrParamAsgns);
                                      If Length(InputProcName)>0 Then
                                         WriteLn(Out,' __throw_cluster__('+ID+','+tran(ChainNames,ChainSubsts,InputProcName)+',__Direction__); \')
                                      Else
                                         WriteLn(Out,' __throw_cluster__('+ID+',1,__Direction__); \');
                                      If Length(InputProcName)>0 Then
                                         WriteLn(Out,' if ('+tran(ChainNames,ChainSubsts,InputProcName)+' == 1) { \');
                                      WriteLn(Out,'    if (!__chain_plan__) { \');
                                      WriteLn(Out,'       cout<<"Default throw link from "<<reinterpret_cast<void *>(&_call_'+ID+')<<"["<<plan_linear_num()<<"] does not exist"<<endl; \');
                                      WriteLn(Out,'       exit(-1); \');
                                      WriteLn(Out,'    } \');
                                      WriteLn(Out,'    __abstract_list<_throw_'+ID+'> * __throw_list__ = (__abstract_list<_throw_'+ID+'> *) __chain_plan__; \');
                                      WriteLn(Out,'    __throw_locking__; \');
                                      WriteLn(Out,'    __throw_list__->push_##__Direction__(__dummy_throw__); \');
                                      WriteLn(Out,'    __throw_unlocking__; \');
                                      WriteLn(Out,'    __throw_signal__; \');
                                      If Length(InputProcName)>0 Then
                                         Begin
                                           WriteLn(Out,' } else { \');
                                           WriteLn(Out,'    __throw_substitute__('+ID+','+tran(ChainNames,ChainSubsts,InputProcName)+'); \');
                                           WriteLn(Out,'    __throw_locking__; \');
                                           WriteLn(Out,'    __throw_list__->push_##__Direction__(__dummy_throw__); \');
                                           WriteLn(Out,'    __throw_unlocking__; \');
                                           WriteLn(Out,'    __throw_signal__; \');
                                           WriteLn(Out,' } \');
                                         End;
                                      WriteLn(Out,'} while(0)')
                                    End;

                                 CorrectParamNames(_ParamNames,S);
                                 CorrectParamNames(ParamNames,S);
                                 CorrectParamNames(_rParamNames,S1); {!!!!!!}
                                 CorrectParamNames(rParamNames,S1); {!!!!!!}

                                 WriteLn(Out,'#define '+ID+'('+S+' \');
                                 WriteLn(Out,'   caller__'+ID+'(0'+ParamNames);
                                 WriteLn(Out,'#define __continue__'+ID+'('+S+' \');
                                 WriteLn(Out,'   caller__'+ID+'(1'+ParamNames);
                                 WriteLn(Out,'#define caller__'+ID+'(__continue'+ParamNames+' \');
                                 If StaticFlag=smKept Then
                                    Begin
                                       WriteLn(Out,'  do { \');
                                       WriteLn(Out,'   if (n__events_'+ID+'+1 >=__events_'+ID+'.size()) { \');
                                       WriteLn(Out,'     __events_'+ID+'.push_back(new '+Ldecl+'<'+PrmStruct+'>'+Format(Lparm,[PrmStruct, PrmStruct, PrmStruct])+'); \');
                                       WriteLn(Out,'   } \');
                                       WriteLn(Out,'   n__events_'+ID+'++; \');
                                       WriteLn(Out,'   reent_list<'+Ldecl+'<'+PrmStruct+'> *>::iterator it = __events_'+ID+'.begin(); \');
                                       WriteLn(Out,'   for (int iit = 0; iit < n__events_'+ID+'; iit++, it++); \');
                                       WriteLn(Out,'   _events_'+ID+' = *it; \');
                                       WriteLn(Out,'   __'+ID+'__(__continue'+ParamNames+'; \');
                                       WriteLn(Out,'   n__events_'+ID+'--; \');
                                       WriteLn(Out,'   it = __events_'+ID+'.begin(); \');
                                       WriteLn(Out,'   for (int iit = 0; iit < n__events_'+ID+'; iit++, it++); \');
                                       WriteLn(Out,'   _events_'+ID+' = *it; \');
                                       WriteLn(Out,'  } while(0)')
                                    End
                                 Else
                                    WriteLn(Out,'   __'+ID+'__(__continue'+ParamNames);
                                 WriteLn(Out,'#undef __NOT_THROWING__');
                                 If ChainMode Then
                                    WriteLn(Out,'#define __NOT_THROWING__ 0')
                                 Else
                                    WriteLn(Out,'#define __NOT_THROWING__ 1');
                                 WriteLn(Out,'#ifdef _OPENMP');
                                   WriteLn(Out,TypeID,' ',Proc,'(__reent_event * __signaler__, __reent_event * __next_signaler__, int __throw_stage__,'+
                                                            ' void * __chain_plan__, plan_lock_t * __chain_lock__, omp_lock_t * __start_lock__, plan_lock_t * __plan_lock__, omp_lock_t * __continue_lock__, '+
                                                            'char * __parallel_flag__, char * __continue_plan__, '+Ldecl+'<',PrmStruct,'> * __event_list__, int __nprocs__',Params,';');
                                   WriteLn(Out,'inline ',TypeID,' __'+ID+'__(char __continue__, int __nprocs__'+
                                               Copy(Params,1,Length(Params)-1)+
                                               ', __reent_event * p__signaler__ = NULL, __reent_event * __next_signaler__ = NULL, '+
                                               'int __throw_stage__ = 0, void * p__chain_plan__ = NULL, plan_lock_t * p__chain_lock__ = NULL, plan_lock_t * p__plan_lock__ = NULL, '+Ldecl+'<',PrmStruct,'> * p__event_list__ = NULL)');
                                   WriteLn(Out,'{');
                                   If StaticFlag=smDynamic Then
                                      WriteLn(Out,' '+Ldecl+'<'+PrmStruct+'>& _events_'+ID+' = p__event_list__ ? *p__event_list__ : *new '+Ldecl+'<'+PrmStruct+'>'+Format(Lparm,[PrmStruct, PrmStruct, PrmStruct])+';');
                                   WriteLn(Out,' char __val_parallel_flag__ = 0;');
                                   WriteLn(Out,' char * __parallel_flag__   = &__val_parallel_flag__;');
                                   WriteLn(Out,' omp_lock_t __start_lock__, __free_lock__, __continue_lock__;');
                                   If TypeID <> 'void' Then
                                      WriteLn(Out,' ',TypeID,' __ret__;');
                                   WriteLn(Out,' plan_lock_t v__plan_lock__;');
                                   WriteLn(Out,' plan_lock_t& __plan_lock__ = p__plan_lock__ ? *p__plan_lock__ : v__plan_lock__;');
                                   If Length(d_eli)<>0 Then
                                      Begin
                                        WriteLn(Out,' map<'+TypeTaskID+',char> * use_ids = new map<'+TypeTaskID+',char>();');
                                        S2:=',use_ids'
                                      End
                                   Else
                                      S2:='';
                                   WriteLn(Out,' '+PrmStruct+' _dummy_;');
                                   WriteLn(Out,' int __num_threads__    = (__nprocs__ & 0x3FF) ? (__nprocs__ & 0x3FF) : omp_get_max_threads();');
                                   WriteLn(Out,' int __val_free_count__ = __num_threads__;');
                                   WriteLn(Out,' int * __free_count__   = &__val_free_count__;');
                                   WriteLn(Out,' char __val_continue_plan__ = 1+__continue__;');
                                   WriteLn(Out,' char * __continue_plan__ = &__val_continue_plan__;');
                                   WriteLn(Out,' __reent_event __v_signaler__;');
                                   WriteLn(Out,' __reent_event& __signaler__ = p__signaler__ ? *p__signaler__ : __v_signaler__;');
                                   WriteLn(Out,' '+_pRedDummies);
                                   WriteLn(Out,' if (!p__signaler__) __init_reent_event(&__signaler__);');
                                   WriteLn(Out,' omp_init_lock(&__start_lock__);');
                                   WriteLn(Out,' if (!p__plan_lock__) plan_init_lock(&__plan_lock__);');
                                   WriteLn(Out,' omp_init_lock(&__free_lock__);');
                                   WriteLn(Out,' omp_init_lock(&__continue_lock__);');
                                   WriteLn(Out,' if (__nprocs__ & 0x18000) {');
                                   WriteLn(Out,'    char __parallelize__ = __add_group_node(plan_topology_num(),"topology",reinterpret_cast<void *>(&_call_'+ID+'),plan_linear_num(),p__event_list__,p__plan_lock__,p__signaler__);');
                                   WriteLn(Out,'    if (__parallelize__ & 6) __topology_barrier(plan_topology_num());');
                                   WriteLn(Out,' }');
                                   WriteLn(Out,' #pragma omp parallel shared(__start_lock__,__free_lock__,__free_count__,__num_threads__,__continue_plan__,__parallel_flag__'+S2+') private(_dummy_) num_threads(__num_threads__)');
                                   WriteLn(Out,' {');
                                   WriteLn(Out,'  int __thread_id__ = omp_get_thread_num();');
                                   WriteLn(Out,'  int StopFlag = 0;');
                                   WriteLn(Out,' '+Ldecl+'<'+PrmStruct+'>::iterator ev_search;');
                                   If Length(TaskIf)<>0 Then
                                      WriteLn(Out,' '+TypeTaskID+' id;');
                                   WriteLn(Out,' '+pRedDummies);
                                   WriteLn(Out,'  __START_LOCK__(__num_threads__,&__start_lock__);');
                                   WriteLn(Out,'  if (!__continue__ && __thread_id__==0) {' );
                                   WriteLn(Out,'     omp_set_lock(&__free_lock__);');
                                   WriteLn(Out,'     (*__free_count__)--;');
                                   WriteLn(Out,'     omp_unset_lock(&__free_lock__);');
                                   If (Length(TaskReset)<>0) Or (Length(TaskSet)<>0) Then
                                      WriteLn(Out,'     id = '+NameTaskID+';');
                                   If Length(TaskReset)<>0 Then
                                      Begin
                                        Write(Out,'     ');
                                        If Length(TaskEmpty)<>0 Then
                                           Write(Out,'if (id!=('+TaskEmpty+')) ');
                                        WriteLn(Out,TaskReset+';')
                                      End;
                                   If TypeID = 'void' Then
                                      WriteLn(Out,'     ',Proc+'(&__signaler__,__next_signaler__,__throw_stage__,p__chain_plan__,p__chain_lock__,&__start_lock__,&__plan_lock__,&__continue_lock__,__parallel_flag__,__continue_plan__,&'+oEvs+rParamNames+';')
                                   Else
                                      WriteLn(Out,'     __ret__ = ',Proc+'(&__signaler__,__next_signaler__,__throw_stage__,p__chain_plan__,p__chain_lock__,&__start_lock__,&__plan_lock__,&__continue_lock__,__parallel_flag__,__continue_plan__,&'+oEvs+rParamNames+';');
                                   If Length(TaskSet)<>0 Then
                                      Begin
                                        Write(Out,'     ');
                                        If Length(TaskEmpty)<>0 Then
                                           Write(Out,'if (id!=('+TaskEmpty+')) ');
                                        WriteLn(Out,TaskSet+';')
                                      End;
                                   WriteLn(Out,'     omp_set_lock(&__free_lock__);');
                                   WriteLn(Out,'     (*__free_count__)++;');
                                   WriteLn(Out,'     omp_unset_lock(&__free_lock__);');
                                   WriteLn(Out,'     '+pRedModifs);
                                   WriteLn(Out,'  }');
                                   WriteLn(Out,'  while (!StopFlag)');
                                   WriteLn(Out,'    {');
                                   WriteLn(Out,'     int EmptyFlag;');
                                   WriteLn(Out,'     omp_set_lock(&__continue_lock__);');
                                   WriteLn(Out,'     StopFlag = !(*__continue_plan__);');
                                   WriteLn(Out,'     omp_unset_lock(&__continue_lock__);');
                                   WriteLn(Out,'     if (!StopFlag) {');
                                   WriteLn(Out,'        int HasMarker;');
                                   WriteLn(Out,'        int FreeProcs;');
                                   WriteLn(Out,'        char HasTask;');
                                   WriteLn(Out,'        char __parallel_flag_store__ = 0;');
                                   WriteLn(Out,'        do {');
                                   WriteLn(Out,'          int PopMarker = 0;');
                                   WriteLn(Out,'          HasMarker = 0;');
                                   WriteLn(Out,'          HasTask = 0;');
                                   WriteLn(Out,'          plan_set_lock(&__plan_lock__);');
                                   WriteLn(Out,'          __parallel_flag_store__ = *__parallel_flag__;');
                                   WriteLn(Out,'          omp_set_lock(&__free_lock__);');
                                   WriteLn(Out,'          FreeProcs = *__free_count__;');
                                   WriteLn(Out,'          omp_unset_lock(&__free_lock__);');
                                   WriteLn(Out,'          EmptyFlag = '+oEvs+'.empty();');
                                   WriteLn(Out,'          if (!EmptyFlag) {');
                                   WriteLn(Out,'             ev_search = '+oEvs+'.begin();');
                                   If Length(TaskIf)<>0 Then
                                      Begin
                                        WriteLn(Out,'             while (!HasTask && ev_search!='+oEvs+'.end()) {');
                                        WriteLn(Out,'               _dummy_ = *ev_search;');
                                        WriteLn(Out,'               if (_dummy_.Flags & 1) HasTask = 1;');
                                        WriteLn(Out,'               else {');
                                        WriteLn(Out,'                 id = _dummy_.'+NameTaskID+';');
                                        If Length(d_eli)<>0 Then
                                           Begin
                                             Write(Out,'                 if (');
                                             With TaskDependsList Do
                                               For F:=0 To Count-1 Do
                                                 Begin
                                                   Write(Out,'('+Strings[F]+')');
                                                   If F<Count-1 Then Write(Out,'&&')
                                                 End;
                                             WriteLn(Out,')')
                                           End;
                                        WriteLn(Out,'                 HasTask = ('+TaskIf+');');
                                        WriteLn(Out,'                 if (!HasTask) ++ev_search;');
                                        WriteLn(Out,'               }');
                                        WriteLn(Out,'             }');
                                      End
                                   Else
                                      Begin
                                        WriteLn(Out,'             HasTask = 1;');
                                        WriteLn(Out,'             _dummy_   = '+oEvs+'.front();')
                                      End;
                                   WriteLn(Out,'             if (HasTask)');
                                   WriteLn(Out,'                if (HasMarker = _dummy_.Flags & 1)');
                                   WriteLn(Out,'                   if (*__parallel_flag__) {');
                                   WriteLn(Out,'                      PopMarker = FreeProcs==__num_threads__;');
                                   WriteLn(Out,'                      if (PopMarker) {');
                                   WriteLn(Out,'                         int __i;');
                                   WriteLn(Out,'                         plan_unset_lock(&__plan_lock__);');
                                   WriteLn(Out,'                         __signal_reent_event(&__signaler__);');
                                   WriteLn(Out,'                         #pragma omp barrier');
                                   WriteLn(Out,'                         #pragma omp for schedule(static,1) private(__i) ordered nowait');
                                   WriteLn(Out,'                           for (__i=0; __i<__num_threads__; __i++)');
                                   WriteLn(Out,'                               #pragma omp ordered');
                                   WriteLn(Out,'                                 {');
                                   WriteLn(Out,'                                  plan_set_lock(&__plan_lock__);');
                                   WriteLn(Out,'                                  if (__i==0) {');
                                   WriteLn(Out,'                                     '+oEvs+'.pop_front();');
                                   WriteLn(Out,'                                     *__parallel_flag__ = 0;');
                                   WriteLn(Out,'                                     __parallel_flag_store__ = 0;');
                                   WriteLn(Out,'                                  }');
                                   WriteLn(Out,'                                 }');
                                   WriteLn(Out,'                      }');
                                   WriteLn(Out,'                   }');
                                   WriteLn(Out,'                   else');
                                   WriteLn(Out,'                      '+oEvs+'.pop_front();');
                                   WriteLn(Out,'                else {');
                                   WriteLn(Out,'                   '+oEvs+'.erase(ev_search);');
                                   WriteLn(Out,'                   omp_set_lock(&__free_lock__);');
                                   WriteLn(Out,'                   (*__free_count__)--;');
                                   WriteLn(Out,'                   omp_unset_lock(&__free_lock__);');
                                   WriteLn(Out,'                   FreeProcs--;');
                                   WriteLn(Out,'                }');
                                   WriteLn(Out,'             bool _IsEmpty = '+oEvs+'.empty();');
                                   WriteLn(Out,'             plan_unset_lock(&__plan_lock__);');
                                   WriteLn(Out,'             if (!_IsEmpty)');
                                   WriteLn(Out,'                __signal_reent_event(&__signaler__);');
                                   WriteLn(Out,'          }');
                                   WriteLn(Out,'          else if (FreeProcs==__num_threads__) {');
                                   WriteLn(Out,'               plan_unset_lock(&__plan_lock__);');
                                   WriteLn(Out,'               __signal_reent_event(&__signaler__);');
                                   WriteLn(Out,'          }');
                                   WriteLn(Out,'          else __wait_reent_event(&__signaler__,&__plan_lock__);');
                                   WriteLn(Out,'          if (PopMarker) __START_LOCK__(__num_threads__,&__start_lock__);');
                                   WriteLn(Out,'          StopFlag = EmptyFlag && !PopMarker && FreeProcs==__num_threads__;');
                                   WriteLn(Out,'          _Yield();');
                                   WriteLn(Out,'        } while (HasMarker || EmptyFlag && !StopFlag || !EmptyFlag && !HasTask);');
                                   WriteLn(Out,'        if (!StopFlag) {');
                                   WriteLn(Out,'          ',STParamReasgns);
                                   If (Length(d_eli)<>0) Or (Length(TaskSet)<>0) Then
                                      WriteLn(Out,'          id = _dummy_.'+NameTaskID+';');
                                   If (Length(d_eli)<>0) Then
                                      Begin
                                        If Length(TaskEmpty)<>0 Then
                                           WriteLn(Out,'           if (id!=('+TaskEmpty+')) {');
                                        WriteLn(Out,'           plan_set_lock(&__plan_lock__);');
                                        WriteLn(Out,'           (*use_ids)[id] = 1;');
                                        WriteLn(Out,'           plan_unset_lock(&__plan_lock__);');
                                        If Length(TaskEmpty)<>0 Then
                                           WriteLn(Out,'           }')
                                      End;
                                   WriteLn(Out,'          if (__parallel_flag_store__ == 2) {');
                                   If TypeID = 'void' Then
                                      WriteLn(Out,'            __atomic_'+ID+'('+Copy(STParamDummies, 13 {eliminate ',__nprocs__,'}, Length(STParamDummies)-1)+');')
                                   Else
                                      Begin
                                        WriteLn(Out,'            ',TypeID,' l__ret__ = __atomic_'+ID+'('+Copy(STParamDummies, 13 {eliminate ',__nprocs__,'}, Length(STParamDummies)-1)+');');
                                        WriteLn(Out,'            #pragma omp critical(__ret__)');
                                        WriteLn(Out,'            {');
                                        WriteLn(Out,'             __ret__ = l__ret__;');
                                        WriteLn(Out,'            }')
                                      End;
                                   WriteLn(Out,'          } else {');
                                   If TypeID = 'void' Then
                                      WriteLn(Out,'            '+Proc+'(&__signaler__,__next_signaler__,__throw_stage__,p__chain_plan__,p__chain_lock__,'+
                                                                    '&__start_lock__,&__plan_lock__,&__continue_lock__,__parallel_flag__,__continue_plan__,&'+oEvs+STParamDummies+');')
                                   Else
                                      Begin
                                        WriteLn(Out,'            ',TypeID,' l__ret__ = '+Proc+'(&__signaler__,__next_signaler__,__throw_stage__,p__chain_plan__,p__chain_lock__,'+
                                                                      '&__start_lock__,&__plan_lock__,&__continue_lock__,__parallel_flag__,__continue_plan__,&'+oEvs+STParamDummies+');');
                                        WriteLn(Out,'            #pragma omp critical(__ret__)');
                                        WriteLn(Out,'            {');
                                        WriteLn(Out,'             __ret__ = l__ret__;');
                                        WriteLn(Out,'            }')
                                      End;
                                   WriteLn(Out,'          }');
                                   WriteLn(Out,'          if (*__continue_plan__==2) __AFTER_CONTINUE(__NOT_THROWING__,&__continue_lock__,__continue_plan__);');
                                   If Length(TaskSet)<>0 Then
                                      Begin
                                        Write(Out,'          ');
                                        If Length(TaskEmpty)<>0 Then
                                           Write(Out,'if (id!=('+TaskEmpty+')) ');
                                        WriteLn(Out,TaskSet+';')
                                      End;
                                   If (Length(d_eli)<>0) Then
                                      Begin
                                        If Length(TaskEmpty)<>0 Then
                                           WriteLn(Out,'           if (id!=('+TaskEmpty+')) {');
                                        WriteLn(Out,'           plan_set_lock(&__plan_lock__);');
                                        WriteLn(Out,'           use_ids->erase(use_ids->find(id));');
                                        WriteLn(Out,'           plan_unset_lock(&__plan_lock__);');
                                        If Length(TaskEmpty)<>0 Then
                                           WriteLn(Out,'           }')
                                      End;
                                   WriteLn(Out,'          omp_set_lock(&__free_lock__);');
                                   WriteLn(Out,'          (*__free_count__)++;');
                                   WriteLn(Out,'          omp_unset_lock(&__free_lock__);');
                                   WriteLn(Out,'          '+pRedModifs);
                                   WriteLn(Out,'        }');
                                   WriteLn(Out,'        _Yield();');
                                   WriteLn(Out,'     }');
                                   WriteLn(Out,'    }');
                                   WriteLn(Out,'  if (__thread_id__==0 && !(*__parallel_flag__)) omp_unset_lock(&__start_lock__);');
                                   WriteLn(Out,' }');
                                   If Length(d_eli)<>0 Then
                                      WriteLn(Out,' delete use_ids;');
                                   WriteLn(Out,' omp_destroy_lock(&__start_lock__);');
                                   WriteLn(Out,' if (!p__signaler__) __destroy_reent_event(&__signaler__);');
                                   WriteLn(Out,' if (!p__plan_lock__) plan_destroy_lock(&__plan_lock__);');
                                   WriteLn(Out,' omp_destroy_lock(&__free_lock__);');
                                   WriteLn(Out,' omp_destroy_lock(&__continue_lock__);');
                                   WriteLn(Out,' '+pRedModifs_);
                                   If StaticFlag=smDynamic Then
                                      WriteLn(Out,' if (!p__event_list__) delete &_events_'+ID+';');
                                   If TypeID <> 'void' Then
                                      WriteLn(Out,' return __ret__;');
                                   WriteLn(Out,'}');
                                   If ChainMode Then
                                      Begin
                                        WriteLn(Out,'#define __chain_call_'+ID+'__(__throw_stage__,__parallelize__,__init__,__events__,__plan_lock__,'+
                                                    '__signaler__,__next_signaler__,__next_events__,__next_lock__,__counter__,__counter_lock__'+_ParamNames+' \');
                                        WriteLn(Out,'do { \');
                                        WriteLn(Out,' '+Ldecl+'<'+PrmStruct+'> * __EVENTS__ = ('+Ldecl+'<'+PrmStruct+'> *) __events__; \');
                                        WriteLn(Out,' int __thread_id__ = omp_get_thread_num(); \');
                                        WriteLn(Out,' char val__continue_plan__  = 1; \');
                                        WriteLn(Out,' char * __continue_plan__  = &val__continue_plan__; \');
                                        WriteLn(Out,' char __parallel_flag__ = 0; \');
                                        WriteLn(Out,' char __GO__ = 1; \');
                                        WriteLn(Out,' '+_eRedDummies+' \');
                                        WriteLn(Out,' '+PrmStruct+' '+ParamDummy+'; \');
                                        WriteLn(Out,' int __nprocs_mask__ = 0; \');
                                        WriteLn(Out,' if (__init__) { \');
                                        WriteLn(Out,'     __'+ID+'__(0'+
                                                                    Copy(_rParamNames,1,Length(_rParamNames)-1)+
                                                                    ',__signaler__,__next_signaler__,__throw_stage__,__next_events__,__next_lock__,__plan_lock__,__EVENTS__); \');
                                        WriteLn(Out,' '+_eRedModifs+' \');
                                        WriteLn(Out,'     __nprocs_mask__ = 0x18000; \');
                                        WriteLn(Out,' } \');
                                        WriteLn(Out,' while (__GO__) { \');
                                        WriteLn(Out,'   __GO__ = __parallelize__ ? 0 : !__EVENTS__->empty(); \');
                                        WriteLn(Out,'   while (__parallelize__ && !__GO__) { \');
                                        WriteLn(Out,'     plan_set_lock(__plan_lock__); \');
                                        WriteLn(Out,'     __GO__ = !__EVENTS__->empty(); \');
                                        WriteLn(Out,'     if (!__GO__) { \');
                                        WriteLn(Out,'        omp_set_lock(__counter_lock__); \');
                                        WriteLn(Out,'        if (__parallelize__ & 2) \');
                                        WriteLn(Out,'           if (*__counter__ < 0) { \');
                                        WriteLn(Out,'              omp_unset_lock(__counter_lock__); \');
                                        WriteLn(Out,'              plan_unset_lock(__plan_lock__); \');
                                        WriteLn(Out,'              break; \');
                                        WriteLn(Out,'           } else { \');
                                        WriteLn(Out,'              omp_unset_lock(__counter_lock__); \');
                                        WriteLn(Out,'              if (__signaler__) __wait_reent_event(__signaler__,__plan_lock__); \');
                                        WriteLn(Out,'              else plan_unset_lock(__plan_lock__); \');
                                        WriteLn(Out,'           } \');
                                        WriteLn(Out,'        else if (*__counter__ == __thread_id__) { \');
                                        WriteLn(Out,'           (*__counter__)++; \');
                                        WriteLn(Out,'           omp_unset_lock(__counter_lock__); \');
                                        WriteLn(Out,'           plan_unset_lock(__plan_lock__); \');
                                        WriteLn(Out,'           if (__next_signaler__) __signal_reent_event(__next_signaler__); \');
                                        WriteLn(Out,'           break; \');
                                        WriteLn(Out,'        } else { \');
                                        WriteLn(Out,'           omp_unset_lock(__counter_lock__); \');
                                        WriteLn(Out,'           if (__signaler__) __wait_reent_event(__signaler__,__plan_lock__); \');
                                        WriteLn(Out,'           else plan_unset_lock(__plan_lock__); \');
                                        WriteLn(Out,'        } \');
                                        WriteLn(Out,'     } \');
                                        WriteLn(Out,'     else { \');
                                        WriteLn(Out,'        '+ParamDummy+' = __EVENTS__->front(); \');
                                        WriteLn(Out,'        __EVENTS__->pop_front(); \');
                                        WriteLn(Out,'        plan_unset_lock(__plan_lock__); \');
                                        WriteLn(Out,'     } \');
                                        WriteLn(Out,'     __instead_signal_yield(); \');
                                        WriteLn(Out,'   } \');
                                        WriteLn(Out,'   if (__GO__) { \');
                                        WriteLn(Out,'    if (!__parallelize__) { \');
                                        WriteLn(Out,'       '+ParamDummy+' = __EVENTS__->front(); \');
                                        WriteLn(Out,'       __EVENTS__->pop_front(); \');
                                        WriteLn(Out,'    } \');
                                        WriteLn(Out,'    '+ResetDummies+' \');
                                        WriteLn(Out,'    ',ParamReasgns,' \');
                                        WriteLn(Out,'    __'+ID+'__(0'+
                                                                    StringReplace(rParamDummies,'__nprocs__','__nprocs__&(~__nprocs_mask__)',[])+
                                                                    ',__signaler__,__next_signaler__,__throw_stage__,__next_events__,__next_lock__,__plan_lock__,__EVENTS__); \');
                                        WriteLn(Out,'    '+_eRedModifs+' \');
                                        WriteLn(Out,'    __nprocs_mask__ = 0x18000; \');
                                        WriteLn(Out,'   } \');
                                        WriteLn(Out,' } \');
                                        WriteLn(Out,'} while(0)');

                                        WriteLn(Out,'#define mpi__chain_call_'+ID+'__(__throw_stage__,__parallelize__,__init__,__events__,__plan_lock__,'+
                                                    '__signaler__,__next_signaler__,__next_events__,__next_lock__,tag_base'+_ParamNames+' \');
                                        WriteLn(Out,'do { \');
                                        WriteLn(Out,' '+Ldecl+'<'+PrmStruct+'> * __EVENTS__ = ('+Ldecl+'<'+PrmStruct+'> *) __events__; \');
                                        WriteLn(Out,' long long next_id = reinterpret_cast<long long>(__next_events__); \');
                                        WriteLn(Out,' char val__continue_plan__  = 1; \');
                                        WriteLn(Out,' char * __continue_plan__  = &val__continue_plan__; \');
                                        WriteLn(Out,' char __parallel_flag__ = 0; \');
                                        WriteLn(Out,' char __GO__ = 1; \');
                                        WriteLn(Out,' '+_eRedDummies+' \');
                                        WriteLn(Out,' '+PrmStruct+' '+ParamDummy+'; \');
                                        WriteLn(Out,' int __nprocs_mask__ = 0; \');
                                        WriteLn(Out,' if (__init__) { \');
                                        WriteLn(Out,'     __'+ID+'__(0'+
                                                                    Copy(_rParamNames,1,Length(_rParamNames)-1)+
                                                                    ',__signaler__,__next_signaler__,__throw_stage__,__next_events__,__next_lock__,__plan_lock__,__EVENTS__); \');
                                        WriteLn(Out,' '+_eRedModifs+' \');
                                        WriteLn(Out,'     __nprocs_mask__ = 0x18000; \');
                                        WriteLn(Out,' } \');
                                        WriteLn(Out,' while (__GO__) { \');
                                        WriteLn(Out,'   __GO__ = __parallelize__ ? 0 : !__EVENTS__->empty(); \');
                                        WriteLn(Out,'   while (__parallelize__ && !__GO__) { \');
                                        WriteLn(Out,'     plan_set_lock(__plan_lock__); \');
                                        WriteLn(Out,'     __GO__ = !__EVENTS__->empty(); \');
                                        WriteLn(Out,'     if (!__GO__) { \');
                                        WriteLn(Out,'        plan_unset_lock(__plan_lock__); \');
                                        WriteLn(Out,'        if (__parallelize__ & 2) { \');
                                        WriteLn(Out,'           MPI_Status status; \');
                                        WriteLn(Out,'           if (__exited_topology((((__nprocs__)>>10) & 0x1F)/*plan_linear_num()*/)) break; \');
                                        WriteLn(Out,'           int quit_detected; \');
                                        WriteLn(Out,'           MPI_Iprobe(MPI_ANY_SOURCE, tag_base, MPI_COMM_WORLD, &quit_detected, &status); \');
                                        WriteLn(Out,'           if (quit_detected) { \');
                                        WriteLn(Out,'              MPI_Status status1; \');
                                        WriteLn(Out,'              MPI_Recv(NULL, 0, MPI_BYTE, status.MPI_SOURCE, tag_base, MPI_COMM_WORLD, &status1); \');
                                        WriteLn(Out,'              break; \');
                                        WriteLn(Out,'           } else { \');
                                        WriteLn(Out,'              int item_received; \');
                                        WriteLn(Out,'              do { \');
                                        WriteLn(Out,'                 MPI_Iprobe(MPI_ANY_SOURCE, tag_base+2, MPI_COMM_WORLD, &item_received, &status); \');
                                        WriteLn(Out,'                 if (item_received) { \');
                                        WriteLn(Out,'                    MPI_Status status1; \');
                                        WriteLn(Out,'                    int first; \');
                                        WriteLn(Out,'                    MPI_Recv(&first, 1, MPI_INT, status.MPI_SOURCE, tag_base+2, MPI_COMM_WORLD, &status1); \');
                                        WriteLn(Out,'                    MPI_Recv(&'+ParamDummy+', sizeof('+ParamDummy+'), MPI_BYTE, status.MPI_SOURCE, tag_base+2, MPI_COMM_WORLD, &status1); \');
                                        WriteLn(Out,'                    plan_set_lock(__plan_lock__); \');
                                        WriteLn(Out,'                    if (first) __EVENTS__->push_front('+ParamDummy+'); \');
                                        WriteLn(Out,'                    else __EVENTS__->push_back('+ParamDummy+'); \');
                                        WriteLn(Out,'                    plan_unset_lock(__plan_lock__); \');
                                        WriteLn(Out,'                 } \');
                                        WriteLn(Out,'              } while (item_received); \');
                                        WriteLn(Out,'           } \');
                                        WriteLn(Out,'        } else { \');
                                        WriteLn(Out,'           if (__throw_stage__ == 0) { \');
                                        WriteLn(Out,'              if (next_id >= 0) MPI_Send(NULL, 0, MPI_BYTE, next_id, tag_base+1, MPI_COMM_WORLD); \');
                                        WriteLn(Out,'              break; \');
                                        WriteLn(Out,'           } \');
                                        WriteLn(Out,'           MPI_Status status; \');
                                        WriteLn(Out,'           int seq_quit_detected; \');
                                        WriteLn(Out,'           MPI_Iprobe(MPI_ANY_SOURCE, tag_base+1, MPI_COMM_WORLD, &seq_quit_detected, &status); \');
                                        WriteLn(Out,'           if (seq_quit_detected) { \');
                                        WriteLn(Out,'              MPI_Status status1; \');
                                        WriteLn(Out,'              MPI_Recv(NULL, 0, MPI_BYTE, status.MPI_SOURCE, tag_base+1, MPI_COMM_WORLD, &status1); \');
                                        WriteLn(Out,'              if (next_id >= 0) MPI_Send(NULL, 0, MPI_BYTE, next_id, tag_base+1, MPI_COMM_WORLD); \');
                                        WriteLn(Out,'              break; \');
                                        WriteLn(Out,'           } else { \');
                                        WriteLn(Out,'              int item_received; \');
                                        WriteLn(Out,'              do { \');
                                        WriteLn(Out,'                 MPI_Iprobe(MPI_ANY_SOURCE, tag_base+2, MPI_COMM_WORLD, &item_received, &status); \');
                                        WriteLn(Out,'                 if (item_received) { \');
                                        WriteLn(Out,'                    MPI_Status status1; \');
                                        WriteLn(Out,'                    int first; \');
                                        WriteLn(Out,'                    MPI_Recv(&first, 1, MPI_INT, status.MPI_SOURCE, tag_base+2, MPI_COMM_WORLD, &status1); \');
                                        WriteLn(Out,'                    MPI_Recv(&'+ParamDummy+', sizeof('+ParamDummy+'), MPI_BYTE, status.MPI_SOURCE, tag_base+2, MPI_COMM_WORLD, &status1); \');
                                        WriteLn(Out,'                    plan_set_lock(__plan_lock__); \');
                                        WriteLn(Out,'                    if (first) __EVENTS__->push_front('+ParamDummy+'); \');
                                        WriteLn(Out,'                    else __EVENTS__->push_back('+ParamDummy+'); \');
                                        WriteLn(Out,'                    plan_unset_lock(__plan_lock__); \');
                                        WriteLn(Out,'                 } \');
                                        WriteLn(Out,'              } while (item_received); \');
                                        WriteLn(Out,'           } \');
                                        WriteLn(Out,'        } \');
                                        WriteLn(Out,'     } \');
                                        WriteLn(Out,'     else { \');
                                        WriteLn(Out,'        '+ParamDummy+' = __EVENTS__->front(); \');
                                        WriteLn(Out,'        __EVENTS__->pop_front(); \');
                                        WriteLn(Out,'        plan_unset_lock(__plan_lock__); \');
                                        WriteLn(Out,'     } \');
                                        WriteLn(Out,'     __instead_signal_yield(); \');
                                        WriteLn(Out,'   } \');
                                        WriteLn(Out,'   if (__GO__) { \');
                                        WriteLn(Out,'    if (!__parallelize__) { \');
                                        WriteLn(Out,'       '+ParamDummy+' = __EVENTS__->front(); \');
                                        WriteLn(Out,'       __EVENTS__->pop_front(); \');
                                        WriteLn(Out,'    } \');
                                        WriteLn(Out,'    '+ResetDummies+' \');
                                        WriteLn(Out,'    ',ParamReasgns,' \');
                                        WriteLn(Out,'    __'+ID+'__(0'+
                                                                    StringReplace(rParamDummies,'__nprocs__','__nprocs__&(~__nprocs_mask__)',[])+
                                                                    ',__signaler__,__next_signaler__,__throw_stage__,__next_events__,__next_lock__,__plan_lock__,__EVENTS__); \');
                                        WriteLn(Out,'    '+_eRedModifs+' \');
                                        WriteLn(Out,'    __nprocs_mask__ = 0x18000; \');
                                        WriteLn(Out,'   } \');
                                        WriteLn(Out,' } \');
                                        WriteLn(Out,'} while(0)');
                                      End;
                                   WriteLn(Out,TypeID,' ',Proc,'(__reent_event * __signaler__, __reent_event * __next_signaler__,'+
                                                            ' int __throw_stage__, void * __chain_plan__, plan_lock_t * __chain_lock__, omp_lock_t * __start_lock__, plan_lock_t * __plan_lock__, omp_lock_t * __continue_lock__,'+
                                               ' char * __parallel_flag__, char * __continue_plan__, '+Ldecl+'<',PrmStruct,'> * __event_list__, int __nprocs__',Params,L.AnlzLine);
                                 WriteLn(Out,'#else');
                                   WriteLn(Out,TypeID,' ',Proc,'(int __num_stages__, int __throw_stage__, void * __chain_plan__, char * __parallel_flag__, char * __continue_plan__, '+Ldecl+'<',PrmStruct,'> * __event_list__, int __nprocs__',Params,';');
                                   WriteLn(Out,'inline ',TypeID,' __'+ID+'__(char __continue__, int __nprocs__'+
                                               Copy(Params,1,Length(Params)-1)+
                                               ', int __num_stages__ = 1, int __throw_stage__ = 0, void * p__chain_plan__ = NULL, '+Ldecl+'<',PrmStruct,'> * p__event_list__ = NULL)');
                                   WriteLn(Out,'{');
                                   If StaticFlag=smDynamic Then
                                      Begin
                                        WriteLn(Out,' '+Ldecl+'<'+PrmStruct+'> _'+Evs+' = '+Ldecl+'<'+PrmStruct+'>'+Format(Lparm,[PrmStruct, PrmStruct, PrmStruct])+';');
                                        WriteLn(Out,' '+Ldecl+'<'+PrmStruct+'>& '+Evs+' = p__event_list__ ? *p__event_list__ : _'+Evs+';')
                                      End;
                                   WriteLn(Out,' char val__continue_plan__ = 1+__continue__;');
                                   WriteLn(Out,' char * __continue_plan__  = &val__continue_plan__;');
                                   WriteLn(Out,' char __parallel_flag__ = 0;');
                                   If TypeID <> 'void' Then
                                      Begin
                                        WriteLn(Out,' ',TypeID,' __ret__;');
                                        RetAssgn := '__ret__ = '
                                      End
                                   Else
                                      RetAssgn := '';
                                   WriteLn(Out,' '+RedDummies);
                                   WriteLn(Out,' '+PrmStruct+' '+ParamDummy+';');
                                   WriteLn(Out,' if (!__continue__) {');
                                   WriteLn(Out,'    ',RetAssgn,Proc+'(__num_stages__,__throw_stage__,p__chain_plan__,&__parallel_flag__,&val__continue_plan__,&'+Evs+rParamNames+';');
                                   WriteLn(Out,'    '+RedModifs);
                                   WriteLn(Out,' }');
                                   WriteLn(Out,' while (val__continue_plan__ && !'+Evs+'.empty())');
                                   WriteLn(Out,'   {');
                                   WriteLn(Out,'    '+ParamDummy+' = '+Evs+'.front();');
                                   WriteLn(Out,'    '+Evs+'.pop_front();');
                                   WriteLn(Out,'    ',ParamReasgns);
                                   WriteLn(Out,'    ',RetAssgn,Proc+'(__num_stages__,__throw_stage__,p__chain_plan__,&__parallel_flag__,&val__continue_plan__,&'+Evs+rParamDummies+');');
                                   WriteLn(Out,'    '+RedModifs);
                                   WriteLn(Out,'    if (val__continue_plan__==2) val__continue_plan__ = 1;');
                                   WriteLn(Out,'   }');
                                   If TypeID <> 'void' Then
                                      WriteLn(Out,' return __ret__;');
                                   WriteLn(Out,'}');
                                   If ChainMode Then
                                      Begin
                                        WriteLn(Out,'#define __chain_call_'+ID+'__(__num_stages__,__throw_stage__,__init__,__events__,__next_events__'+_ParamNames+' \');
                                        WriteLn(Out,'do { \');
                                        WriteLn(Out,' '+Ldecl+'<'+PrmStruct+'> * __EVENTS__ = ('+Ldecl+'<'+PrmStruct+'> *) __events__; \');
                                        WriteLn(Out,' char val__continue_plan__  = 1; \');
                                        WriteLn(Out,' char * __continue_plan__  = &val__continue_plan__; \');
                                        WriteLn(Out,' char __parallel_flag__ = 0; \');
                                        WriteLn(Out,' '+_eRedDummies+' \');
                                        WriteLn(Out,' '+PrmStruct+' '+ParamDummy+'; \');
                                        WriteLn(Out,' if (__init__) { \');
                                        WriteLn(Out,'    __'+ID+'__(0'+Copy(_rParamNames,1,Length(_rParamNames)-1)+
                                                         ',__num_stages__,__throw_stage__,__next_events__,__EVENTS__); \');
                                        WriteLn(Out,'    '+_eRedModifs+' \');
                                        WriteLn(Out,' } \');
                                        WriteLn(Out,' while (!__EVENTS__->empty()) \');
                                        WriteLn(Out,'   { \');
                                        WriteLn(Out,'    '+ParamDummy+' = __EVENTS__->front(); \');
                                        WriteLn(Out,'    __EVENTS__->pop_front(); \');
                                        WriteLn(Out,'    ',ParamReasgns,' \');
                                        WriteLn(Out,'    __'+ID+'__(0'+rParamDummies+',__num_stages__,__throw_stage__,__next_events__,__EVENTS__); \');
                                        WriteLn(Out,'    '+_eRedModifs+' \');
                                        WriteLn(Out,'   } \');
                                        WriteLn(Out,'} while(0)');
                                      End;
                                   WriteLn(Out,TypeID,' ',Proc,'(int __num_stages__, int __throw_stage__, void * __chain_plan__, char * __parallel_flag__, char * __continue_plan__, '+Ldecl+'<',PrmStruct,'> * __event_list__, int __nprocs__',Params,L.AnlzLine);
                                 WriteLn(Out,'#endif')
                               End
                            Else If Not IsDeclaration Then
                               Begin
                                 WritePlanMacroses(Out,ID,_ParamNames, LocGlobs, _Names, Ldecl);
                                 If ChainMode Then
                                    begin
                                      WriteThrowMacroses(Out,ID,_ThrParamNames);
                                      FunctionThrowParams := ThrParamNames
                                    end;
                                 WriteLn(Out,'#ifdef _OPENMP');
                                   WriteLn(Out,TypeID,' ',Proc,'(__reent_event * __signaler__, __reent_event * __next_signaler__, int __throw_stage__, void * __chain_plan__, plan_lock_t * __chain_lock__,'+
                                                         ' omp_lock_t * __start_lock__, plan_lock_t * __plan_lock__, omp_lock_t * __continue_lock__, '+
                                                         'char * __parallel_flag__, char * __continue_plan__, '+Ldecl+'<',PrmStruct,'> * __event_list__, int __nprocs__',Params,L.AnlzLine);
                                 WriteLn(Out,'#else');
                                   WriteLn(Out,TypeID,' ',Proc,'(int __num_stages__, int __throw_stage__, void * __chain_plan__, char * __parallel_flag__, char * __continue_plan__, '+Ldecl+'<',PrmStruct,'> * __event_list__, int __nprocs__',Params,L.AnlzLine);
                                 WriteLn(Out,'#endif')
                               End
                          End
                     end
                  Else
                     begin
                       WriteLn(Out,S);
                       If (Length(SoftFunctionText) > 0) And Not ReadFunction Then
                          begin
                            WriteLn(Out);
                            WriteAtomicMacroses(Out, FunctionParamNames, FunctionThrowParams);
                            S := '';  // current word
                            S1 := ''; // final text
                            S2 := ''; // previous word
                            G := 0; // position of previous word
                            AtomizeFlag := False;
                            SoftAtomizeFlag := False;
                            VectorizeFlag := False;
                            For F := 1 To Length(SoftFunctionText) Do
                              If SoftFunctionText[F] In IdentSet Then
                                 S := S + SoftFunctionText[F]
                              Else
                                 begin
                                   If Length(S) > 0 Then
                                      begin
                                        If CompareText(S, idplan_group_atomize) = 0 Then AtomizeFlag := True;
                                        If CompareText(S, idplan_group_soft_atomize) = 0 Then SoftAtomizeFlag := True;
                                        If CompareText(S, idplan_group_vectorize) = 0 Then VectorizeFlag := True;
                                        If CompareText(S, idplan_group_typize) = 0 Then VectorizeFlag := True;
                                        If (S = FunctionID) And (S2 = 'continue') Then
                                           For K := 1 To Length('continue') Do
                                               S1[G+K-1] := ' ';
                                        If S = FunctionID Then S := '__soft_atomic_' + FunctionID;
                                        G := Length(S1) + 1;
                                        S1 := S1 + S;
                                        S2 := S
                                      end;
                                   S := '';
                                   S1 := S1 + SoftFunctionText[F]
                                 end;
                            If Length(S) > 0 Then
                               begin
                                 If CompareText(S, idplan_group_atomize) = 0 Then AtomizeFlag := True;
                                 If CompareText(S, idplan_group_soft_atomize) = 0 Then SoftAtomizeFlag := True;
                                 If CompareText(S, idplan_group_vectorize) = 0 Then VectorizeFlag := True;
                                 If CompareText(S, idplan_group_typize) = 0 Then VectorizeFlag := True;
                                 If (S = FunctionID) And (S2 = 'continue') Then
                                    For K := 1 To Length('continue') Do
                                        S1[G+K-1] := ' ';
                                 If S = FunctionID Then S := '__soft_atomic_' + FunctionID;
                                 S1 := S1 + S
                               end;
                            // Check plan_group_atomize and comment body if this directive is absent
                            If Not SoftAtomizeFlag Then
                               begin
                                 S1 := StringReplace(S1, '*/', '*/ /*', [rfReplaceAll]);
                                 F := Pos(LeftFBracket, S1);
                                 Insert(CRLF+'/*', S1, F + 1);
                                 If FunctionType <> 'void' Then
                                    Insert(CRLF+' '+FunctionType+' __dummy__;', S1, F + 1)
                               end;
                            F := Length(S1);
                            While S1[F] <> RightFBracket Do
                              Dec(F);
                            // Check plan_group_atomize and comment body if this directive is absent
                            If SoftAtomizeFlag Then
                               S2 := CRLF
                            Else
                               begin
                                 S2 := '*/'+CRLF;
                                 If FunctionType <> 'void' Then
                                    S2 := S2 + ' return __dummy__;'+CRLF
                               end;
                            Insert(S2, S1, F);
                            WriteLn(Out, S1);
                            SoftFunctionText := ''
                          end;
                       If (Length(FunctionText) > 0) And Not ReadFunction Then
                          begin
                            WriteLn(Out);
                            WriteAtomicMacroses(Out, FunctionParamNames, FunctionThrowParams);
                            FunctionParamNames := '';
                            FunctionThrowParams := '';
                            S := '';  // current word
                            S1 := ''; // final text
                            S2 := ''; // previous word
                            G := 0; // position of previous word
                            AtomizeFlag := False;
                            SoftAtomizeFlag := False;
                            VectorizeFlag := False;
                            For F := 1 To Length(FunctionText) Do
                              If FunctionText[F] In IdentSet Then
                                 S := S + FunctionText[F]
                              Else
                                 begin
                                   If Length(S) > 0 Then
                                      begin
                                        If CompareText(S, idplan_group_atomize) = 0 Then AtomizeFlag := True;
                                        If CompareText(S, idplan_group_soft_atomize) = 0 Then SoftAtomizeFlag := True;
                                        If CompareText(S, idplan_group_vectorize) = 0 Then VectorizeFlag := True;
                                        If CompareText(S, idplan_group_typize) = 0 Then VectorizeFlag := True;
                                        If (S = FunctionID) And (S2 = 'continue') Then
                                           For K := 1 To Length('continue') Do
                                               S1[G+K-1] := ' ';
                                        If S = FunctionID Then S := '__atomic_' + FunctionID;
                                        G := Length(S1) + 1;
                                        S1 := S1 + S;
                                        S2 := S
                                      end;
                                   S := '';
                                   S1 := S1 + FunctionText[F]
                                 end;
                            If Length(S) > 0 Then
                               begin
                                 If CompareText(S, idplan_group_atomize) = 0 Then AtomizeFlag := True;
                                 If CompareText(S, idplan_group_soft_atomize) = 0 Then SoftAtomizeFlag := True;
                                 If CompareText(S, idplan_group_vectorize) = 0 Then VectorizeFlag := True;
                                 If CompareText(S, idplan_group_typize) = 0 Then VectorizeFlag := True;
                                 If (S = FunctionID) And (S2 = 'continue') Then
                                    For K := 1 To Length('continue') Do
                                        S1[G+K-1] := ' ';
                                 If S = FunctionID Then S := '__atomic_' + FunctionID;
                                 S1 := S1 + S
                               end;
                            // Check plan_group_atomize and comment body if this directive is absent
                            If Not AtomizeFlag Then
                               begin
                                 S1 := StringReplace(S1, '*/', '*/ /*', [rfReplaceAll]);
                                 F := Pos(LeftFBracket, S1);
                                 Insert(CRLF+'/*', S1, F + 1);
                                 If FunctionType <> 'void' Then
                                    Insert(CRLF+' '+FunctionType+' __dummy__;', S1, F + 1)
                               end;
                            F := Length(S1);
                            While S1[F] <> RightFBracket Do
                              Dec(F);
                            // Check plan_group_atomize and comment body if this directive is absent
                            If AtomizeFlag Then
                               S2 := CRLF
                            Else
                               begin
                                 S2 := '*/'+CRLF;
                                 If FunctionType <> 'void' Then
                                    S2 := S2 + ' return __dummy__;'+CRLF
                               end;
                            Insert(S2, S1, F);
                            WriteLn(Out, S1);
                            FunctionText := ''
                          end;
                       If (Length(GPUFunctionText) > 0) And Not ReadFunction Then
                          begin
                            WriteLn(Out);
                            S := '';  // current word
                            S1 := ''; // final text
                            S2 := ''; // previous word
                            G := 0; // position of previous word
                            For F := 1 To Length(GPUFunctionText) Do
                              If GPUFunctionText[F] In IdentSet Then
                                 S := S + GPUFunctionText[F]
                              Else
                                 begin
                                   If Length(S) > 0 Then
                                      begin
                                        If (S = FunctionID) And (S2 = 'continue') Then
                                           For K := 1 To Length('continue') Do
                                               S1[G+K-1] := ' ';
                                        If S = FunctionID Then S := 'gpu_' + FunctionID;
                                        G := Length(S1) + 1;
                                        S1 := S1 + S;
                                        S2 := S
                                      end;
                                   S := '';
                                   S1 := S1 + GPUFunctionText[F]
                                 end;
                            If Length(S) > 0 Then
                               begin
                                 If (S = FunctionID) And (S2 = 'continue') Then
                                    For K := 1 To Length('continue') Do
                                        S1[G+K-1] := ' ';
                                 If S = FunctionID Then S := 'gpu_' + FunctionID;
                                 S1 := S1 + S
                               end;
                            F := Length(S1);
                            While S1[F] <> RightFBracket Do
                              Dec(F);
                            // Check plan_group_atomize and comment body if this directive is absent
                            S2 := '/* return */'+CRLF;
                            Insert(S2, S1, F);
                            If IsVectorized Then
                               Begin
                                 WriteLn(Out,'#ifdef __REENT_GPU__');
                                 SL := TStringList.Create;
                                 SL.Text := S1;
                                 WriteString(Out, 'gpu_'+FunctionID, SL);
                                 SL.Free;
                                 WriteLn(Out,'#endif')
                               End
                            Else If VectorizeFlag Then
                               Begin
                                 WriteLn('Vectorizing: vector mode is off now in function ',TLine(Lines.Objects[LCounter-1]).GetDescription);
                                 Halt(-1)
                               End;
                            GPUFunctionText := ''
                          end
                     end
                end;
              ClusteredArrID := '';
              Inc(LCounter)
            End;
          If L.Error Then
             WriteLn('Parse error',TLine(Lines.Objects[LCounter-2]).GetDescription);
          L.Free;
          L1.Free;
          Reducts.Free;
          LocGlobs.Free;
          Declared.Free;
          TypeMaps.Free;
          ProgGPU.Free;
          With Chain Do
            Begin
              For F:=0 To Count-1 Do
                  DisposeStr(PString(Objects[F]));
              Free
            End;
          ChainNames.Free;
          ChainSubsts.Free;
          TaskDependsList.Free;
          With DeclarationList Do
            Begin
              For F:=0 To Count-1 Do
                  DisposeStr(PString(Objects[F]));
              Free
            End;
          IDList.Free;
          _Names.Free;
          Substs.Free;
          With Defines Do
            Begin
              For F := 0 To Count - 1 Do
                  DisposeStr(PString(Objects[F]));
              Free
            End;
          With Lines Do
            Begin
              For F := 0 To Count - 1 Do
                  If Assigned(Objects[F]) Then
                     Objects[F].Free;
              Free
            End;
          With Files Do
            Begin
              For F := 0 To Count - 1 Do
                  If Assigned(Objects[F]) Then
                     Objects[F].Free;
              Free
            End;
          Topology.Free;
          Close(Out)
        End
end.

