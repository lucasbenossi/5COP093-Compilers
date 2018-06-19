PROGRAM TC04;
VAR I,J,K:INTEGER;
BEGIN
    I:=1;J:=1;K:=1;
    WHILE (I<11) DO
    BEGIN
        WHILE (J<12) DO
        BEGIN
            WHILE (K<13) DO
                BEGIN
                    K:=K+3;
                END;
            J:=J+2;
            I:=4;
        END;
    I:=I+1;
    END;
END.
