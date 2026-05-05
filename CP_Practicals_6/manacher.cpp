#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class ManachersAlgorithm {
private:
    // Preprocess string by adding '#' between characters
    // This helps handle both even and odd length palindromes uniformly
    string preprocessString(string s) {
        string processed = "^#";  // Start with ^ as boundary
        
        for (int i = 0; i < s.length(); i++) {
            processed += s[i];
            processed += "#";
        }
        
        processed += "$";  // End with $ as boundary
        return processed;
    }
    
public:
    // Find the longest palindromic substring using Manacher's Algorithm
    string findLongestPalindrome(string s) {
        if (s.length() == 0) {
            cout << "Empty string provided" << endl;
            return "";
        }
        
        // Preprocess the string
        string processed = preprocessString(s);
        int n = processed.length();
        
        // Array to store the radius of palindrome at each center
        int* palinRadius = new int[n];
        
        // Center of the "rightmost" palindrome
        int center = 0;
        
        // Right boundary of the "rightmost" palindrome
        int rightBoundary = 0;
        
        // Variables to track the longest palindrome
        int maxRadius = 0;
        int centerOfLongest = 0;
        
        cout << "Processed string: " << processed << endl;
        cout << endl;
        
        // Expand around each center
        for (int i = 1; i < n - 1; i++) {
            // Mirror position with respect to center
            int mirror = 2 * center - i;
            
            // If i is within the right boundary, we can use previously calculated values
            if (i < rightBoundary) {
                palinRadius[i] = min(rightBoundary - i, palinRadius[mirror]);
            }
            
            // Try to expand palindrome centered at i
            while (i + 1 + palinRadius[i] < n && i - 1 - palinRadius[i] >= 0 && 
                   processed[i + 1 + palinRadius[i]] == processed[i - 1 - palinRadius[i]]) {
                palinRadius[i]++;
            }
            
            // If palindrome centered at i extends past rightBoundary, update center and rightBoundary
            if (i + palinRadius[i] > rightBoundary) {
                center = i;
                rightBoundary = i + palinRadius[i];
            }
            
            // Track the longest palindrome
            if (palinRadius[i] > maxRadius) {
                maxRadius = palinRadius[i];
                centerOfLongest = i;
            }
        }
        
        cout << "Palindrome radii: ";
        for (int i = 1; i < n - 1; i++) {
            cout << palinRadius[i] << " ";
        }
        cout << endl << endl;
        
        // Extract the longest palindrome from original string
        int startIdx = (centerOfLongest - maxRadius) / 2;
        string result = s.substr(startIdx, maxRadius);
        
        delete[] palinRadius;
        
        return result;
    }
};

int main() {
    ManachersAlgorithm manacher;
    
    cout << "=== MANACHER'S ALGORITHM ===" << endl;
    cout << "Finding the longest palindromic substring in linear time" << endl;
    cout << endl;
    
    // Test case 1
    cout << "--- TEST CASE 1 ---" << endl;
    string test1 = "babad";
    cout << "Input string: " << test1 << endl;
    string result1 = manacher.findLongestPalindrome(test1);
    cout << "Longest palindrome: " << result1 << endl;
    cout << "Length: " << result1.length() << endl;
    cout << endl;
    
    // Test case 2
    cout << "--- TEST CASE 2 ---" << endl;
    string test2 = "abacabad";
    cout << "Input string: " << test2 << endl;
    string result2 = manacher.findLongestPalindrome(test2);
    cout << "Longest palindrome: " << result2 << endl;
    cout << "Length: " << result2.length() << endl;
    cout << endl;
    
    // Test case 3
    cout << "--- TEST CASE 3 ---" << endl;
    string test3 = "racecar";
    cout << "Input string: " << test3 << endl;
    string result3 = manacher.findLongestPalindrome(test3);
    cout << "Longest palindrome: " << result3 << endl;
    cout << "Length: " << result3.length() << endl;
    cout << endl;
    
    // Test case 4
    cout << "--- TEST CASE 4 ---" << endl;
    string test4 = "aabbaabb";
    cout << "Input string: " << test4 << endl;
    string result4 = manacher.findLongestPalindrome(test4);
    cout << "Longest palindrome: " << result4 << endl;
    cout << "Length: " << result4.length() << endl;
    cout << endl;
    
    // Test case 5 - Single character
    cout << "--- TEST CASE 5 ---" << endl;
    string test5 = "a";
    cout << "Input string: " << test5 << endl;
    string result5 = manacher.findLongestPalindrome(test5);
    cout << "Longest palindrome: " << result5 << endl;
    cout << "Length: " << result5.length() << endl;
    cout << endl;
    
    // Test case 6 - No palindrome
    cout << "--- TEST CASE 6 ---" << endl;
    string test6 = "abcdef";
    cout << "Input string: " << test6 << endl;
    string result6 = manacher.findLongestPalindrome(test6);
    cout << "Longest palindrome: " << result6 << endl;
    cout << "Length: " << result6.length() << endl;
    
    return 0;
}
