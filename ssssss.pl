true(river_volga).
true(pupil_vasya).
true(true).

calculate(List, Res):-
    analyze(List, Res).

analyze(['('|T], Res) :-
    append(Exp, [')'|Rest], T),
    analyze(Exp, Res1),
    analyze(Rest, Res2),
    append(Res1, Res2, Res).

analyze([A, '&', B | T], Res):-
    true(A),
    true(B),
    valid(A),
    valid(B),
    analyze([true|T], Res),
    !.

analyze([A, '&', B | T], Res):-
    valid(A),
    valid(B),
    analyze([false|T], Res).

analyze([A, '=>', B | T], Res):-
    (\+ true(A); true(B)),
    valid(A),
    valid(B),
    analyze([true|T], Res),
    !.

analyze([A, '=>', B | T], Res):-
    valid(A),
    valid(B),
    analyze([false|T], Res).

analyze(['~', B | T], Res):-
    true(B),
    valid(B),
    analyze([false|T], Res),
    !.

analyze(['~', B | T], Res):-
    valid(B),
    analyze([true|T], Res).

analyze([A, 'V', B | T], Res):-
    (true(A); true(B)),
    valid(A),
    valid(B),
    analyze([true|T], Res),
    !.

analyze([A, 'V', B | T], Res):-
    valid(A),
    valid(B),
    analyze([false|T], Res).

analyze([A|[B|T]], Res):-
    analyze([B|T], Y),
    [B|T] \= Y,
    analyze([A|Y], Res),
    !.

analyze(X, X).

valid(X):-
    \+ member(X, ['(', ')', '&', '=>', '~', 'V']).