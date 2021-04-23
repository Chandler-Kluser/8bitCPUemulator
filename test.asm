#ruledef
{
    LDA {value} => 0b000 @ value`5
    LIA {value} => 0b001 @ value`5
	STA {value} => 0b010 @ value`5
	SWP {value} => 0b011 @ value`5
	JMP {value} => 0b100 @ value`5
	JEZ {value} => 0b101 @ value`5
	ADD {value} => 0b110 @ value`5
	SUB {value} => 0b111 @ value`5
}


LIA 0
ADD 1
STA 8
JMP 1