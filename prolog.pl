true(river_volga).
true(pupil_vasya).
true(true).

calculate(List,Res):-
	analyze(List,[Res]).

% parentheses
analyze(['(',true,')'|T],Res):-
	analyze([true|T],Res).
analyze(['(',false,')'|T],[false|T]):-
	analyze([false|T],Res).

% & operator
analyze([A,'&',B | T], Res):-
	true(A),
	true(B),
	valid(A),
	valid(B),
	analyze([true|T],Res),
	!.

analyze([A,'&',B | T], Res):-
	valid(A),
	valid(B),
	analyze([false|T],Res).

% => operator
analyze([A,'=>',B | T], Res):-
	(not(true(A));true(B)),
	valid(A),
	valid(B),
	analyze([true|T],Res),
	!.

analyze([A,'=>',B | T], Res):-
	valid(A),
	valid(B),
	analyze([false|T],Res).

% ~ operator
analyze(['~',B | T], Res):-
	true(B),
	valid(B),
	analyze([false|T],Res),
	!.

analyze(['~',B | T], Res):-
	valid(B),
	analyze([true|T],Res).

analyze([A,'&',B | T], Res):-
	valid(A),
	valid(B),
	analyze([false|T],Res).

analyze([A,'V',B | T], Res):-
	(true(A);true(B)),
	valid(A),
	valid(B),
	analyze([true|T],Res),
	!.

analyze([A,'V',B | T], Res):-
	valid(A),
	valid(B),
	analyze([false|T],Res).

analyze([A|[B|T]],Res):-
	analyze([B|T],Y),
	[B|T] \= Y,
	analyze([A|Y],Res),!.

analyze(X,X).

valid(X):-
	X \= '&',
    X \= 'V',
	X \= '=>',
	X \= '~',
    X \= '(',
	X \= ')'.