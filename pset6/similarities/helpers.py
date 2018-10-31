from nltk.tokenize import sent_tokenize

# this is my own helper


def get_substring(a, n):
    substrings_arr = []
    for i in range(len(a)):
        if len(a[i:n + i]) == n:
            substrings_arr.append(a[i:n + i])
    return substrings_arr

# this are the cs50 functions


def lines(a, b):
    """Return lines in both a and b"""
    # TODO
    a_set = set(a.splitlines())
    b_set = set(b.splitlines())
    final_set = a_set.intersection(b_set)
    return list(final_set)


def sentences(a, b):
    """Return sentences in both a and b"""
    # TODO
    a_set = set(sent_tokenize(a))
    b_set = set(sent_tokenize(b))
    final_set = a_set.intersection(b_set)
    return list(final_set)


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    # TODO
    a_set = set(get_substring(a, n))
    b_set = set(get_substring(b, n))
    final_set = a_set.intersection(b_set)
    return list(final_set)
