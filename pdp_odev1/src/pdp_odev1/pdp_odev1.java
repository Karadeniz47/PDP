/** 
* 
* @author İsmail Alper Karadeniz ismailalperkaradeniz@gmail.com
* @since 5.04.2024
* <p> 
*  pdp_odev1
* </p> 
*/ 


package pdp_odev1;
import java.io.*;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;

public class pdp_odev1 {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Lütfen GitHub deposunun URL'sini girin: ");
        String repoUrl = scanner.nextLine();
        scanner.close();

        String repoName = repoUrl.substring(repoUrl.lastIndexOf("/") + 1);
        String localPath = "repo";

        try {
            downloadAndExtractRepo(repoUrl + "/archive/master.zip", localPath, repoName);
            System.out.println("Repo başarıyla indirildi: " + repoName);

            // Indirilen repo'nun içindeki Java dosyalarını analiz et
            analyzeJavaFiles(localPath + File.separator + repoName);
        } catch (IOException e) {
            System.out.println("Depo indirilirken bir hata oluştu: " + e.getMessage());
        }
    }

    private static void downloadAndExtractRepo(String repoUrl, String localPath, String repoName) throws IOException {
        URL url = new URL(repoUrl);
        try (InputStream in = url.openStream();
             ZipInputStream zipIn = new ZipInputStream(in)) {

            ZipEntry entry;
            while ((entry = zipIn.getNextEntry()) != null) {
                if (!entry.isDirectory()) {
                    String filePath = localPath + File.separator + repoName + File.separator + entry.getName();
                    String[] pathComponents = entry.getName().split("/");
                    if (pathComponents.length > 1) {
                        String folderPath = localPath + File.separator + repoName + File.separator + pathComponents[0];
                        new File(folderPath).mkdirs();
                    }
                    extractFile(zipIn, filePath);
                }
                zipIn.closeEntry();
            }
        }
    }

    private static void extractFile(ZipInputStream zipIn, String filePath) throws IOException {
        File file = new File(filePath);
        if (!file.getParentFile().exists()) {
            file.getParentFile().mkdirs();
        }
        try (BufferedOutputStream out = new BufferedOutputStream(new FileOutputStream(filePath))) {
            byte[] buffer = new byte[1024];
            int bytesRead;
            while ((bytesRead = zipIn.read(buffer)) != -1) {
                out.write(buffer, 0, bytesRead);
            }
        }
    }

    private static void analyzeJavaFiles(String directoryPath) {
        File directory = new File(directoryPath);
        if (!directory.exists()) {
            System.out.println("Belirtilen dizin bulunamadı: " + directoryPath);
            return;
        }

        List<File> javaFiles = getJavaFiles(directory);
        if (javaFiles.isEmpty()) {
            System.out.println("Klonlanan depoda .java uzantılı dosya bulunamadı.");
            return;
        }

        for (File javaFile : javaFiles) {
            analyzeJavaFile(javaFile.getAbsolutePath());
        }
    }

    private static List<File> getJavaFiles(File directory) {
        List<File> javaFiles = new ArrayList<>();
        findJavaFiles(directory, javaFiles);
        return javaFiles;
    }

    private static void findJavaFiles(File directory, List<File> javaFiles) {
        File[] files = directory.listFiles();
        if (files != null) {
            for (File file : files) {
                if (file.isFile() && file.getName().endsWith(".java")) {
                    javaFiles.add(file);
                } else if (file.isDirectory()) {
                    findJavaFiles(file, javaFiles);
                }
            }
        }
    }

    private static void analyzeJavaFile(String filePath) {
        JavaFileAnalyzer analyzer = new JavaFileAnalyzer(filePath);
        analyzer.analyze();
        analyzer.printAnalysis();
    }
}

