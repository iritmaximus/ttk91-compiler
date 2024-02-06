from token import Token

class Parser:
    def __init__(self, parser_reader):
        self.__reader = parser_reader
        self.__data = []
        self.__parsed_data = []

    def read_file(self, filename: str):
        self.__data = self.__reader.read_file(filename)

    def parse(self):
        for line in self.__data:
            line = line.strip()
            self.get_tokens_from_line(line)
        for token in self.__parsed_data:
            print(token)

    def get_tokens_from_line(self, line: str):
        line_and_comments = line.split(";")

        # if there was only comment, no expression
        if len(line_and_comments) > 1:
            # splitting with the char ; removes it so we add it back for parsing
            comment = "; " + line_and_comments[1].strip()
            token = Token(comment)
            self.__parsed_data.append(token.parse())

        # no expression -> skip
        if line_and_comments[0] == "":
            return None

        expression = line_and_comments[0].strip()
        for token_str in expression.split():
            token = Token(token_str.strip(","))
            self.__parsed_data.append(token.parse())


class ParserReader:
    def __init__(self):
        pass

    def read_file(self, filename: str) -> [str]:
        if not filename:
            return []

        with open(filename) as f:
            lines = f.readlines()
        return lines

    def read_args(self):
        pass

