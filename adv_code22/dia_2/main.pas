program dia_2;

var c: Char;
    f: Text;
    input_: String;
    total_pts: integer;
    play_pts: integer;
    oponent_num: integer;
    you_num: integer;

begin
    if (1 = 0) then
        input_ := 'teste.txt'
    else
        input_ := 'input.txt';

    Assign(f, input_);
    Reset(f);
    total_pts := 0;
    while not eof(f) do
    begin
        read(f, c);
        case c of
            'A', 'B', 'C': begin
                play_pts := 0;
                case c of
                    'A': oponent_num := 0;
                    'B': oponent_num := 1;
                    'C': oponent_num := 2;
                end;
            end;
            'X', 'Y', 'Z': begin
                case c of
                    'X': you_num := 0;
                    'Y': you_num := 3;
                    'Z': you_num := 6;
                end;
                play_pts := you_num;

                case (oponent_num + you_num) of
                    1, 3, 8: play_pts := play_pts + 1;
                    2, 4, 6: play_pts := play_pts + 2;
                    0, 5, 7: play_pts := play_pts + 3;
                end;
                (*writeln('pontos na rodada: ', play_pts);
                writeln('  op: ', oponent_num, ' you: ', you_num);*)
                total_pts := total_pts + play_pts;
            end;
            
        end;
    end;
    close(f);
    writeln('Total de pontos e: ', total_pts);
end.

0        pedra
1        papel
2        tesoura
0        lose
3        draw
6        win

pedra: 1
1, 3, 8
papel: 2
2, 4, 6
tesoura: 3
0, 5, 7