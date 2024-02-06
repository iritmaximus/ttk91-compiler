class Token:
    def __init__(self, value: str):
        self.__value = value

    def parse(self):
        if Comment.is_comment(self.__value):
            return Comment(self.__value)

        if Instruction.is_instruction(self.__value):
            return Instruction(self.__value)

        if Label.is_label(self.__value):
            return Label(self.__value)

        if Register.is_register(self.__value):
            return Register(self.__value)

        if Value.is_value(self.__value):
            return Value(self.__value)

        return self

    def __repr__(self):
        return f"Token({self.__value})"


class Instruction(Token):
    data_insructions = ["LOAD", "STORE", "IN", "OUT"]
    arithmetic_instructions = ["ADD", "SUB", "MUL", "DIV", "MOD"]
    logic_instructions = ["AND", "OR", "XOR", "NOT", "SHL", "SHR", "SHRA", "COMP"]
    branching_instructions = ["JUMP", "JNEG", "JZER", "JPOS", "JNNEG", "JNZER", "JNPOS", "JLES", "JEQU", "JGRE", "JNLES", "JNEQU", "JNGRE"]
    stack_instructions = ["PUSH", "POP", "PUSHR", "POPR"]
    subroutine_instructions = ["CALL", "EXIT"]
    systemcall_insructions = ["SVC"]
    compiler_insructions = [ "DEF"]
    macro_instructions = ["EQU", "DC", "DS"]
    other_instructions = ["NOP"]

    all_instructions = data_insructions + arithmetic_instructions + logic_instructions + branching_instructions + stack_instructions + subroutine_instructions + systemcall_insructions + compiler_insructions + macro_instructions + other_instructions

    def __init__(self, instruction: str):
        self.__value = instruction

    @staticmethod
    def is_instruction(string: str) -> bool:
        if string in Instruction.all_instructions:
            return True
        return False

    @staticmethod
    def is_macro(string: str) -> bool:
        # TODO this doesn't take in count the DEF command
        if string in Instruction.macro_instructions:
            return True
        return False

    def __repr__(self):
        return f"Instruction({self.__value})"


class Comment(Token):
    def __init__(self, value: str):
        self.__value = value

    @staticmethod
    def is_comment(value: str) -> bool:
        if ";" in value:
            return True
        return False

    def __repr__(self) -> str:
        return f"Comment({self.__value})"


class Label(Token):
    def __init__(self, value: str):
        self.__value = value

    @staticmethod
    def is_label(value: str) -> bool:
        for char in value:
            if char.isalpha():
                continue
            return False
        return True

    def __repr__(self) -> str:
        return f"Label({self.__value})"

class Register(Token):
    def __init__(self, value: str):
        self.__value = value

    @staticmethod
    def is_register(value: str) -> bool:
        if value[0] != "R":
            return False

        # TODO cap at max register count
        if value[1:].isdigit():
            return True

    def __repr__(self) -> str:
        return f"Register({self.__value})"

class Value(Token):
    def __init__(self, value: str):
        self.__value = value
        if value:
            self.__immediate = True if value[0] == "=" else False
            self.__indirect = True if value[0] == "@" else False
        else:
            self.__immediate = False
            self.__indirect = False


    @staticmethod
    def is_value(value: str) -> bool:
        for char in value:
            if char == "@" or char == "=":
                continue
            if char == "(":
                return True

            if char.isdigit():
                continue

            return False
        return True


    def parse_indexed_value(self):
        pass

    def __repr__(self):
         return f"Value({self.__value}, {self.__immediate}, {self.__indirect})"


class Operator(Token):
    def __init__(self, value: str):
        self.__value = value

    @staticmethod
    def is_operator(value: str):
        pass
