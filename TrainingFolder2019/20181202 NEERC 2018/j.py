n = int(input())
trie = {}
reserved = set()
for tok in input().split():
	cur = trie
	reserved.add(tok)
	for c in tok:
		if c not in cur: cur[c] = {}
		cur = cur[c]
	cur[-1] = True

#print(trie)
m = int(input())
tokens = " ".join([input().split("#")[0] for _ in range(m)]).split()

import string
WORDS = set(string.ascii_lowercase + string.ascii_uppercase + string.digits + "_" + "$")

tokenized = []

def go(tok):
	pref = ""
	len_word = 0
	len_digit = 0
	len_reserved = 0
	cur = trie
	for i in range(len(tok)):
		if len_word == i and tok[i] in WORDS:
			len_word += 1
		if len_digit == i and tok[i].isdigit():
			len_digit += 1
		if tok[i] in cur:
			cur = cur[tok[i]]
			if -1 in cur: 
				len_reserved = i+1
		else:
			cur = {}
	if tok[0].isdigit():
		len_word = 0

	now = max((len_reserved, 10000), (len_word, 1), (len_digit, 2))
	return now

for tok in tokens:
	while tok != "":
		now = go(tok)
		tokenized.append((tok[:now[0]], now[1]))
		tok = tok[now[0]:]

twl = list(string.ascii_lowercase)
for a in string.ascii_lowercase:
	for b in string.ascii_lowercase:
		twl.append(a + b)
for a in string.ascii_lowercase:
	for b in string.ascii_lowercase:
		for c in string.ascii_lowercase:
			twl.append(a + b + c)

twl = list(filter(lambda x: x not in reserved, twl))

twl_pos = 0

word_mapping = {}

for i, v in enumerate(tokenized):
	tok, mode = v
	if mode == 1:
		if tok not in word_mapping:
			word_mapping[tok] = twl[twl_pos]
			twl_pos += 1
		tokenized[i] = (word_mapping[tok], 1)

tokens = [x[0] for x in tokenized]
dap = []

ans = "".join(tokens)
#print(ans)

ans_pos = 0
tok_pos = 0
while len(ans) > 0:
	#print(ans, dap, "\n")
	cur_tok_length = go(ans)[0]
	if len(tokens[tok_pos]) != cur_tok_length:
		dap.append(tokens[tok_pos] + ' ')
	else:
		dap.append(tokens[tok_pos])
	ans = ans[len(tokens[tok_pos]):]
	tok_pos += 1

print(''.join(dap).strip())
#print(tokenized)

#print("\n".join(lines))