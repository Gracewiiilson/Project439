import java.io.*;
import java.util.*;

public class FileSystem {
    private String currentDirectory;
    private Map<String, File> files;

    public FileSystem() {
        currentDirectory = "/";
        files = new HashMap<String, File>();
    }

    public void changeDirectory(String newDirectory) {
        if (newDirectory.startsWith("/")) {
            currentDirectory = newDirectory;
        } else {
            currentDirectory += "/" + newDirectory;
        }
    }

    public String getCurrentDirectory() {
        return currentDirectory;
    }

    public void createFile(String fileName, String content) {
        File newFile = new File(fileName, content);
        files.put(currentDirectory + "/" + fileName, newFile);
    }

    public void writeFile(String fileName, String content) {
        String filePath = currentDirectory + "/" + fileName;
        if (files.containsKey(filePath)) {
            files.get(filePath).setContent(content);
        } else {
            System.out.println("Error: file does not exist.");
        }
    }

    public void deleteFile(String fileName) {
        String filePath = currentDirectory + "/" + fileName;
        if (files.containsKey(filePath)) {
            files.remove(filePath);
        } else {
            System.out.println("Error: file does not exist.");
        }
    }

    public void listFiles() {
        Set<String> fileNames = files.keySet();
        for (String fileName : fileNames) {
            if (fileName.startsWith(currentDirectory)) {
                System.out.println(fileName.substring(currentDirectory.length() + 1));
            }
        }
    }

    public void readFile(String fileName) {
        String filePath = currentDirectory + "/" + fileName;
        if (files.containsKey(filePath)) {
            System.out.println(files.get(filePath).getContent());
        } else {
            System.out.println("Error: file does not exist.");
        }
    }

    public static void main(String[] args) {
        FileSystem fs = new FileSystem();

        fs.createFile("test.txt", "This is a test file.");
        fs.changeDirectory("new_directory");
        fs.createFile("test2.txt", "This is another test file.");
        fs.changeDirectory("/");

        fs.listFiles();
        fs.readFile("test.txt");
        fs.writeFile("test.txt", "This is the new content.");
        fs.readFile("test.txt");
        fs.deleteFile("test.txt");
        fs.listFiles();
    }
}

class File {
    private String name;
    private String content;

    public File(String name, String content) {
        this.name = name;
        this.content = content;
    }

    public String getName() {
        return name;
    }

    public String getContent() {
        return content;
    }

    public void setContent(String newContent) {
        content = newContent;
    }
}

