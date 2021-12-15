import java.util.*;

public class Crack {
    // This and the fib() function is O(n)
    static void allFib(int n) {
        int[] memo = new int[n + 1]; // empty array of 0's
        for (int i = 0; i < n; i++) {
            System.out.println(i + ": " + fib(i, memo));
        }
    }

    public static int fib(int n, int[] memo) {
        if (n <= 0)
            return 0;
        else if (n == 1)
            return 1;
        else if (memo[n] > 0)
            return memo[n];

        memo[n] = fib(n - 1, memo) + fib(n - 2, memo); // O(2) every time
        return memo[n];
    }

    public int powersOf2(int n) {
        if (n < 1) {
            return 0;
        } else if (n == 1) {
            System.out.println(1);
            return 1;
        } else {
            int prev = powersOf2(n / 2);
            int curr = prev * 2;
            System.out.println(curr);
            return curr;
        }
    }

    /**
     * Recursive solution for finding permutation
     *
     * @param t_String the String that you want to get a permutation of
     * @return the permutation of the string
     */
    static ArrayList<String> permutationOfString(String t_String) {
        ArrayList<String> result = new ArrayList<String>();
        if (t_String.length() == 1) { // base case
            result.add(t_String);
        } else if (t_String.length() > 1) {
            // newString is t_String without its last char
            String newString = t_String.substring(0, t_String.length() - 1);
            String lastChar = t_String.substring(t_String.length() - 1);
            ArrayList<String> sub = permutationOfString(newString);
            for (int i = 0; i < sub.size(); i++) { // for each string
                String perm = sub.get(i);
                for (int j = 0; j < perm.length(); j++) { // for each char
                    String addedPerm;
                    if (j == 0) {
                        addedPerm = lastChar + perm;
                        result.add(addedPerm);
                    }
                    String firstHalf = perm.substring(0, j + 1); // "" for "a"
                    String secondHalf = perm.substring(j + 1); // "a" for "a"
                    addedPerm = firstHalf + lastChar + secondHalf; //
                    result.add(addedPerm);
                }
            }
        }
        return result;
    }

    /**
     * 1.1) Is Unique: Implement an algorithm to determine if a string has all
     * unique characters. What if you cannot use additonal data structures?
     */
    static boolean isUnique(String t_String) {
        if (t_String.length() > 128)
            return false;
        HashSet<Character> usedChars = new HashSet<Character>();
        for (int i = 0; i < t_String.length(); i++) {
            if (usedChars.contains(t_String.charAt(i))) {
                if (t_String.charAt(i) == ' ')
                    continue;
                return false;
            } else {
                usedChars.add(t_String.charAt(i));
            }
        }
        return true;
    }

    /**
     * 1.2) Check Permutation: Given two strings, write a method to decide if one is
     * a permutation of the other.
     */
    static boolean checkPermutation(String str1, String str2) {
        HashMap<Character, Integer> occurrences = new HashMap<Character, Integer>();
        for (int i = 0; i < str1.length(); i++) {
            char c = str1.charAt(i);
            int n = 1;
            if (occurrences.containsKey(c))
                n = occurrences.get(c) + 1;
            occurrences.put(c, n);
        }
        for (int j = 0; j < str2.length(); j++) {
            char c = str2.charAt(j);
            if (!occurrences.containsKey(c)) {
                return false;
            } else {
                occurrences.put(c, occurrences.get(c) - 1);
                if (occurrences.get(c) == 0) {
                    occurrences.remove(c);
                }
            }
        }
        return true;
    }

    /**
     * 1.3) URLify: Write a method to replace all spaces in a string with '%20'. You
     * may assume that the string has sufficient space at the end to hold the
     * additional characters, and that you are given the "true" length of the
     * string. Use character array so you can perform this operation in place.
     */
    static char[] urlify(char[] tString, int length) {
        int spaceCount = 0, resultIndex = 0;
        for (int i = 0; i < length; i++)
            if (tString[i] == ' ')
                spaceCount++;
        int trueLength = (length-1) + (spaceCount * 2);
        char[] result = new char[trueLength];

        for (int stringIndex = 0; stringIndex < trueLength; stringIndex++) {
            if (tString[stringIndex] == ' ') {
                result[resultIndex++] = '%';
                result[resultIndex++] = '2';
                result[resultIndex] = '0';
            } else {
                result[resultIndex++] = tString[stringIndex];
            }
        }
        return result;
    }

    // ============================== CHAPTER 2 ==============================

    /**
     * Numbers are randomly generated and stored into an (expanding) array. Keep
     * track of the median
     */
    public static void main(String[] args) {
        char[] a = { 'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', ' ' };
        char[] result = urlify(a, 11);
        String name = "Lam";
        for (int i = 0; i < a.length; i++) {
            System.out.print(result[i]);
        }
    }
}
