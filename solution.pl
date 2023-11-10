day('Чук',  'Понедельник',  0).
day('Чук', 'Вторник', 0).
day('Чук', 'Среда', 0).
day('Чук', 'Четверг', 1).
day('Чук', 'Пятница', 1).
day('Чук', 'Суббота', 1).
day('Чук', 'Воскресенье', 1).
day('Гек', 'Понедельник', 1).
day('Гек', 'Вторник', 0).
day('Гек', 'Среда', 1).
day('Гек', 'Четверг', 0).
day('Гек', 'Пятница', 1).
day('Гек', 'Суббота', 0).
day('Гек', 'Воскресенье', 1).

yesterday('Вторник', 'Понедельник').
yesterday('Среда', 'Вторник').
yesterday('Четверг', 'Среда').
yesterday('Пятница', 'Четверг').
yesterday('Суббота', 'Пятница').
yesterday('Воскресенье', 'Суббота').
yesterday('Понедельник', 'Воскресенье').

different('Чук', 'Гек').
different('Гек', 'Чук').
 
term1(0, First) :- 
    First \= 'Чук'.

term1(1, First) :- 
    First = 'Чук'.

term2(0, Today) :- 
    not(yesterday(Today, 'Воскресенье')).

term2(1, Today) :- 
    yesterday(Today, 'Воскресенье').

term3(0, Today) :- 
    not(yesterday('Пятница', Today)).

term3(1, Today) :- 
    yesterday('Пятница', Today).
    
term4(Second_truth, Second) :- 
    day(Second, 'Среда', Second_truth).

solve :-
    day(First, Today, First_truth),
    different(First, Second),
    day(Second, Today, Second_truth),
    
    term1(First_truth, First),
    term2(First_truth, Today),
    term3(Second_truth, Today),
    term4(Second_truth, Second),
    
    write('First: '), write(First), nl,
    write('Second: '), write(Second), nl,
    write('Today: '), write(Today), nl, !.