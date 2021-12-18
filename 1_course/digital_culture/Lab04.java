import java.io.*;
import java.util.*;
import java.lang.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.charset.*;

class WordForm
{
	String word;
	int count;
	
	public WordForm(String word, int count) {
		this.word = word;
		this.count = count;
	}
}

class Complience {
	int count; // частота встречаемости
	String word; // словоформа
	int levenstain; // расстояние Левенштейна
	
	public Complience(int count, String word, int levenstain) {
		this.count = count;
		this.word = word;
		this.levenstain = levenstain;
	}
}

public class Lab04 {
	
	
	// функция удаления требуемых символов, включая символы переноса строк
	public String replaceSymbols(String in)
	{
		return in.replaceAll("!","")
					.replaceAll("\\?","") // ?
					.replaceAll(",","")
					.replaceAll(";","")
					.replaceAll("\\.","") // .
					.replaceAll(":","")
					.replaceAll("\u00AB","") //«
					.replaceAll("\\(","") // (
					.replaceAll("\\)","") // )
					.replaceAll("\u00BB","") //»
					.replaceAll("\r\n", " "); // перенос строки
	}
	
	
	// функция разбиения текста на слова, возвращает массив всех слов
	public String[] getWords(String in)
	{
		return in.split(" ");
	}
	
	
	// функция преобразования типов Set<String> в String[]
	public static String[] setToArray(Set<String> setOfString) 
    {  
        String[] arrayOfString = new String[setOfString.size()]; 
        int index = 0; 
        for (String str : setOfString) 
            arrayOfString[index++] = str;
		
        return arrayOfString; 
    } 
	
	
	// функция, удаляющая повторы из массива (оставляет уникальные/разные значения)
	public String[] getUnique(String[] words)
	{
		Set<String> set = new LinkedHashSet<String>(Arrays.asList(words));
		return setToArray(set);
	}
	
	
	// функция поиска слова в словаре
	public boolean findInDictionary(String str, ArrayList<WordForm> dict)
	{
		for (int i = 0; i < dict.size(); i++)
			if (str.equals(dict.get(i).word))
				return true;
		return false;
	}
	
	// функция подсчета словоформ, присутствующих в словаре
	public int countDictWords(String[] words, ArrayList<WordForm> dict)
	{
		int count = 0;
		for (int i = 0; i < words.length; i++)
			if (findInDictionary(words[i], dict))
				count++;
		return count;
	}
	
	
	// функция получения минимума из трех чисел (используется в ф-ии подсчета расст. Левенштейна)
	public int min(int n1, int n2, int n3) {
        return Math.min(Math.min(n1, n2), n3);
    }
	
	
	// функция подсчета расстояния Левенштейна для двух передаваемых строк: str1, str2
	public int levenstain(String str1, String str2) {
        int[] Di_1 = new int[str2.length() + 1];
        int[] Di = new int[str2.length() + 1];

        for (int j = 0; j <= str2.length(); j++) {
            Di[j] = j;
        }

        for (int i = 1; i <= str1.length(); i++) {
            System.arraycopy(Di, 0, Di_1, 0, Di_1.length);

            Di[0] = i;
            for (int j = 1; j <= str2.length(); j++) {
                int cost = (str1.charAt(i - 1) != str2.charAt(j - 1)) ? 1 : 0;
                Di[j] = min(
                        Di_1[j] + 1,
                        Di[j - 1] + 1,
                        Di_1[j - 1] + cost
                );
            }
        }

        return Di[Di.length - 1];
    }
	
	
	// функция вывода на экран подходящих слов из словаря
	// возвращает список слов из словаря, подходящих под замену в тексте
	public ArrayList<Complience> getSimilarWords(String[] words, ArrayList<WordForm> dict) {
		
		ArrayList<Complience> result = new ArrayList<Complience>(); // результирующий список слов под замену
		
		for (int i = 0; i < words.length; i++) // перебор всех слов из списка "потенциальных ошибок"
		{
			ArrayList<Complience> compliences = new ArrayList<Complience>(); // потенциальные замены из словаря
																			 // текущего слова
			System.out.print(words[i]);
			
			for (int j = 0; j < dict.size(); j++)
				if (levenstain(words[i], dict.get(j).word) <= 2) // если расстояние Левенштейна <= 2
					compliences.add(new Complience(
						dict.get(j).count, 
						dict.get(j).word,
						levenstain(words[i], dict.get(j).word)
					)); // добавляем в список потенциальных замен
			
			if (compliences.size() >= 0) // если список потенциальных замен из словаря под данное слово не пуст
			{
				Collections.sort(compliences, (o1, o2) -> (o2.count - o1.count)); // сортируем по частоте встречаемости
																				  // в порядке убывания
				Complience matched = compliences.get(0);
				for (int j = 0; j < compliences.size(); j++)
					if (compliences.get(j).levenstain == 1) // проверяем наличие наиболее близкой словоформы
					{
						matched = compliences.get(j);
						break;
					}
				System.out.print(" - " + matched.word + " - " + matched.levenstain + "\n");
				result.add(matched);
			}
			else
			{ // если список потенциальных замен пуст, то замены слову не найдено
				System.out.print(" - не найдено - >2\n");
				result.add(new Complience(-1, "не найдено", -1));
			}
		}
		return result;
	}
	
	public static void main(String[] args) throws IOException {
		String contents = new String(Files.readAllBytes(Paths.get("brain097.txt")), StandardCharsets.UTF_8);
		PrintStream out = new PrintStream(new File("words.txt"));
		PrintStream fin = new PrintStream(new File("final.txt"));
		
		String orig = contents;
		
		// считываем словарь
		Scanner sc = new Scanner(new File("dict1.txt"));

		ArrayList<WordForm> dict = new ArrayList<WordForm>();
		
		while (sc.hasNextLine())
		{
			String[] str = sc.nextLine().split(" ");
			dict.add(new WordForm(new String(str[0].getBytes(), StandardCharsets.UTF_8), Integer.parseInt(str[1])));
		}

		// удаление знаков ! ? , ; . : « ( ) »
		contents = new Lab04().replaceSymbols(contents);
		
		// приведение к нижнему регистру
		contents = contents.toLowerCase();
		
		// получение словоформ
		String[] words = new Lab04().getWords(contents);
		
		// вывод количества словоформ
		System.out.println("Words count: " + words.length);
		
		// получение разных словоформ
		String[] uniqueWords = new Lab04().getUnique(words);
		
		// вывод количества разных словоформ
		System.out.println("Unique words count: " + uniqueWords.length);
		
		// вывод количества разных словоформ, присутствующих в словаре
		int uniqueDictWordsCount = new Lab04().countDictWords(uniqueWords, dict);
		System.out.println("Unique words found in dict1.txt: " + uniqueDictWordsCount);
		
		// вывод количества разных словоформ, не присутствующих в словаре
		System.out.println("Unique words NOT found in dict1.txt: " + (uniqueWords.length - uniqueDictWordsCount));
		
		// поиск различных словоформ, не присутствующих в словаре
		String[] potentialTypos = new String[uniqueWords.length - uniqueDictWordsCount];
		int cur = 0;
		for (int i = 0; i < uniqueWords.length; i++)
			if (!(new Lab04().findInDictionary(uniqueWords[i], dict)))
				potentialTypos[cur++] = uniqueWords[i];
		
		out.print(contents);
		out.close();
		
		System.out.println("\nWords replacements:");
		
		// поиск похожих в словаре и замена в тексте
		ArrayList<Complience> matches = new Lab04().getSimilarWords(potentialTypos, dict);
		
		for (int i = 0; i < matches.size(); i++)
			if (matches.get(i).count != -1)
				orig = orig.replaceAll(potentialTypos[i], matches.get(i).word);

		fin.print(orig);
		fin.close();
		
		// повторяем расчеты для преобразованного текста
		
		
		// получение словоформ
		words = new Lab04().getWords(contents);
		
		// вывод количества словоформ
		System.out.println("\nWords count: " + words.length);
		
		// получение разных словоформ
		uniqueWords = new Lab04().getUnique(words);
		
		// вывод количества разных словоформ
		System.out.println("Unique words count: " + uniqueWords.length);
		
		// вывод количества разных словоформ, присутствующих в словаре
		uniqueDictWordsCount = new Lab04().countDictWords(uniqueWords, dict);
		System.out.println("Unique words found in dict1.txt: " + uniqueDictWordsCount);
		
		// вывод количества разных словоформ, не присутствующих в словаре
		System.out.println("Unique words NOT found in dict1.txt: " + (uniqueWords.length - uniqueDictWordsCount));
		
		
	}
}