from parser import Parser, ParserReader

FILENAME = "example.k91"


def main():
    parser_reader = ParserReader()
    parser = Parser(parser_reader)

    parser.read_file(FILENAME)
    parser.parse()


if __name__ == "__main__":
    main()
