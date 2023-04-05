import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.attribute.PosixFilePermission;
import java.nio.file.attribute.PosixFilePermissions;
import java.util.Set;

public class FileManager
{
    // Define file permissions as a set of PosixFilePermission Objects
    private static final Set<PosixFilePermission> READ_ONLY = PosixFilePermissions.fromString("r--r--r--");
    private static final Set<PosixFilePermission> READ_WRITE = PosixFilePermissions.fromString("rw-rw-rw-");
    private static final Set<PosixFilePermission> EXECUTE_ONLY = PosixFilePermissions.fromString("--x--x--x");


    // Define a method to set file permissions for a specific file
    public void setFilePermissions(String filename, Set<PosixFilePermission>permissions)
    throws IOException
    {
        Path file = Paths.get(filename);
        Files.setPosixFilePermissions(file,permissions);

    }
    //Example Usage 
    public static void main(String[] args)
    {
        FileManager fileManager = new FileManager();

        try{
            // Set the permissions of the file "myfile.txt" to READ_ONLY
            fileManager.setFilePermissions("myfile.txt", READ_ONLY);
            
            // Set the permissions of the file "helloworld.sh" to EXECUTE_ONLY
            fileManager.setFilePermissions("helloworld.sh", EXECUTE_ONLY);
        }
        catch(IOException e){
            System.err.println("Error setting file permissions:" + e.getMessage());
        }
    }

    
}
