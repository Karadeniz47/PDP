/** 
* 
* @author İsmail Alper Karadeniz ismailalperkaradeniz@gmail.com
* @since 5.04.2024
* <p> 
*  JavaFileAnalyzer
* </p> 
*/ 
package pdp_odev1;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.File;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class JavaFileAnalyzer {
	private String filePath; // Dosya yolunu saklamak için yeni bir değişken ekleyin

	private String fileName;
	private int javadocLines;
	private int commentLineNumber;
	
	private int codeLines;
	private int loc;
	private int functionCount;

	public JavaFileAnalyzer(String filePath) {
		this.filePath = filePath; // Dosya yolunu kaydet

		// Dosya adını almak yerine tüm dosya yolunu kaydet
		this.fileName = filePath;

		this.javadocLines = 0;
		this.commentLineNumber = 0;
		this.codeLines = 0;
		this.loc = 0;
		this.functionCount = 0;
	}

	public void analyze() {
		if (!filePath.endsWith(".java")) {
			// Eğer dosya ".java" uzantısına sahip değilse analiz yapma
			return;
		}

		// Dosyada class kontrolü yap
		if (!containsClass()) {
			return;
		}
		 functionCount = countFunctions(filePath);

		try (BufferedReader reader = new BufferedReader(new FileReader(filePath))) {  
			String line;
			boolean isClass = false;
			boolean inComment = false;
			boolean inJavadoc = false;
			boolean inCommentBlock = false;

			while ((line = reader.readLine()) != null) {
				// LOC'yi arttır
				loc++;
				line = line.trim();
				if (line.isEmpty()) {
					continue;
				}

				if (line.startsWith("/**")) {
					// Javadoc satırı
					inJavadoc = true;
					 
					if (line.endsWith("*/")) {
						// Javadoc satırı aynı satırda sonlanıyorsa
						javadocLines++;
						inJavadoc = false;
					}
				}
				else if (line.startsWith("/*")) {
					// Yorum bloğu başlangıcı
					inComment = true;
					
					if (line.endsWith("*/")) {
						// Yorum bloğu aynı satırda sonlanıyorsa
						commentLineNumber++;
						inComment = false;
					}
				} 
				
				else if (line.endsWith("*/")) {
					// Yorum veya Javadoc satırının sonu
					if (inComment) {
						inComment = false;
					} else if (inJavadoc) {
						inJavadoc = false;
					}

				}
				
				else if (inComment) {
					// Yorum bloğu içindeyiz
					commentLineNumber++;
					if (line.endsWith("*/")) {
						inComment = false;
					}

				} else if (inJavadoc) {
					// JavaDoc bloğu içindeyiz
					javadocLines++;
					if (line.endsWith("*/")) {
						inJavadoc = false;
					}
				}

				  else {
					  if(line.startsWith("//"))
					  {
						// Yorum satırı
							commentLineNumber++;
					  }
					  else {
						// Kod satırı
							codeLines++;
							if(line.contains("//"))
							{
								commentLineNumber++;
							}
					  }
				}
				
				
				
			}

		} catch (IOException e) {
			System.err.println("Dosya okunurken bir hata oluştu: " + e.getMessage());
		}
	}

	private boolean containsClass() {
		try (BufferedReader reader = new BufferedReader(new FileReader(filePath))) {
			String line;
			while ((line = reader.readLine()) != null) {
				if (line.contains("class")) {
					return true;
				}
			}
		} catch (IOException e) {
			System.err.println("Dosya okunurken bir hata oluştu: " + e.getMessage());
		}
		return false;
	}

	public static int countFunctions(String filePath) {
        int functionCount = 0;

        try {
            File file = new File(filePath);
            BufferedReader reader = new BufferedReader(new FileReader(file));
            String line;

            // Satırları oku ve her satırı işle
            while ((line = reader.readLine()) != null) {
                // Satırda fonksiyon tanımı var mı kontrol et
                if (containsFunction(line)) {
                    functionCount++;
                }
            }

            reader.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return functionCount;
    }
	
	// Verilen satırın bir fonksiyon tanımı içerip içermediğini kontrol eden metod
    private static boolean containsFunction(String line) {
        // Metodun başlangıçtan sonra ve ardından bir kelime olup olmadığını kontrol eden regex
        Pattern pattern = Pattern.compile("(public|private|protected|static|final|synchronized) +[\\w<>,. ]*\\(");
        Matcher matcher = pattern.matcher(line);
        return matcher.find();
    }

	
	public void printAnalysis() {
		File file = new File(filePath);
		String name = file.getName();
		// Dosyada interface kontrolü yap
		if (!containsClass()) {
			return;
		}
		System.out.println("Sınıf: " + name); // Sınıf adını yaz
		System.out.println("Javadoc Satır Sayısı: " + javadocLines);
		System.out.println("Yorum Satır Sayısı: " + commentLineNumber);
		System.out.println("Kod Satır Sayısı: " + codeLines);
		System.out.println("LOC: " + loc);
		System.out.println("Fonksiyon Sayısı: " + functionCount);
		double yorumSapmaYuzdesi = calculateCommentDeviationPercentage();
		System.out.printf("Yorum Sapma Yüzdesi: %.2f%%\n", yorumSapmaYuzdesi);
		System.out.println("-----------------------------------------");
	}

	private double calculateCommentDeviationPercentage() {
		double yg = ((javadocLines + commentLineNumber) * 0.8) / functionCount;
		double yh = (double) codeLines / functionCount * 0.3;
		return ((100 * yg) / yh) - 100;
	}
}



