func findSubstring(s string, words []string) (result []int) {
	if len(words) == 0 || len(s) == 0 {
		return
	}
	wordLen := len(words[0])
	wordsNum := len(words)

	//将ｗords放入Ｍａｐ中
	wordsMap := map[string]int{}
	for _, word := range words {
		wordsMap[word]++
	}

	length := wordLen * wordsNum

	//使用ｓｔａｒｔ开头长度为ｌｅｎ的窗口滑动
	for start := 0; start < len(s)-length+1; start++ {
		tmpMap := map[string]int{}
		j := 0
		for ; j < length; j += wordLen {
			tmpS := s[start+j : start+j+wordLen]
			if wordsMap[tmpS] != 0 {
				tmpMap[tmpS]++
				if tmpMap[tmpS] > wordsMap[tmpS] {
					break
				}
			} else {
				break
			}

		}
		if j == length {
			result = append(result, start)
		}
	}
	return
}