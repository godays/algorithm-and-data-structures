class Lexer:
    def __init__(self, string: str):
        self.my_str = string
        self.s_len = len(string)
        self.iter = 0
        self.ended = False
        self.finish = "."
        self.alphabet = {'nums': '0123456789', 'ops': "+-*/()"}

    def next(self):
        key = ""
        elem = self.my_str[self.iter]
        if elem in self.alphabet['ops']:
            key = elem
        elif elem == self.finish:
            self.ended = True
        else:
            while elem in self.alphabet['nums']:
                key += elem
                self.iter += 1
                elem = self.my_str[self.iter]
            self.iter -= 1
        self.iter += 1
        return key


input_string = input()
ans = []
lexer = Lexer(input_string)

while not lexer.ended:
    token = lexer.next()
    ans.append(token)

print("\n".join(ans))