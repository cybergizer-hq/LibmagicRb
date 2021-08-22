# LibmagicRb
Adds ability to check mime-type of a file using the libmagic ([magic(4)](https://man7.org/linux/man-pages/man4/magic.4.html)).
It uses native extensions and it's quite performant.

## Pre-Installation
On Linux, you need to install libmagic. The version we recommend is at least 5.36.
But if you have an older version of libmagic, it will compile and work flawlessly but with a few caveats:

+ Many constants (modes and params) will be not defined
+ LibmagicRb::MAGIC_VERSION constant will be set to 0.
+ Few methods will not work.
  some methods that can return a String or Integer will return nil (like setparam and getparam).

[ Do note that the minimum tested version is 5.11, older than that may fail to compile the gem ]

You also need Ruby > 1.9.0 in order to run this gem.

With that info in mind, let's continue to the installation part for your Linux distributions...

#### Arch / Manjaro / Archlabs / Garuda Linux / Hefftor Linux & other Arch Based Linux

```
# pacman -S ruby file gcc make --needed
```

#### Debian / Ubuntu / Linux Mint / Deepin / Pop!_OS / RaspberryPi OS & other Debian Based Linux

```
# apt install ruby libmagic-dev ruby-dev gcc make
```

#### Fedora / Amazon Linux / CentOS & Other RedHat Based Linux

```
# yum install ruby file-devel ruby-devel gcc make
```

#### OpenSUSE

```
zypper in ruby ruby-devel file-devel gcc make
```

#### DragonflyBSD / FreeBSD

Versions upto 0.1.2 is tested on DragonflyBSD (Version 6.0-SYNTH).

```
pkg install ruby devel/ruby-gems gcc gmake
```

#### Mac / Windows

Mac and Windows are currently not tested, hence the support is unknown.

## Installation

Add this line to your application's Gemfile:

```ruby
gem 'libmagic_rb'
```

And then execute:

```
$ bundle install
```

Or install it yourself as:

```
$ gem install libmagic_rb
```

We recommend getting the gem only from Rubygems.org. Do not download this repo as zip, compile to install the gem.
A rubygem version is released after various tests. Any branch here including Master branch can be unstable can even segfault your app. You've been warned!

## Usage
The target of this gem is to add mime-type checking easily.

Using the LibmagicRb class we can check the mime type, EXIF data and other information of a file.

To check a file, you need to pass a hash argument to the FilemagicRb.new():

1. db: Path to the Database (String)
2. file: A file to check (String)
3. mode: Modes of the file (Integer) (Optional, defaults to `LibmagicRb::MAGIC_MIME | LibmagicRb::MAGIC_CHECK | LibmagicRb::MAGIC_SYMLINK`)

### Example 1:

```
require 'libmagic_rb'

cookie = LibmagicRb.new(
    file: '/usr/share/backgrounds/myimage.webp',
    mode: LibmagicRb::MAGIC_MIME | LibmagicRb::MAGIC_CHECK | LibmagicRb::MAGIC_SYMLINK
)

p cookie # =>    #<LibmagicRb:0x000055cf96d8f868 @db="/home/sourav/.gem/ruby/3.0.0/gems/libmagic_rb-0.1.0/data/magic.mgc", @file="/usr/share/backgrounds/myimage.webp", @mode=1106, @closed=false>

# In case The file path needs to be changed
cookie.file = '/usr/share/backgrounds/vienna-5164602.jpg'

p cookie.file    # => "/usr/share/backgrounds/vienna-5164602.jpg"
p cookie.db    # => nil

cookie.check()    # => image/jpeg; charset=binary
cookie.close()    # => #<LibmagicRb:0x000055fa77699818 @closed=true, @db="/home/sourav/.gem/ruby/3.0.0/gems/libmagic_rb-0.1.0/data/magic.mgc", @file="/usr/share/backgrounds/vienna-5164602.jpg", @mode=1106>
cookie.closed?() # => true
```

When the `db:` key is `nil`, it will use NULL as the database file - which gets the database automatically from the system.
You can omit `db: nil` as well for a nil value.

### Example 2:
```
require 'libmagic_rb'

cookie = LibmagicRb.new(
    db: '/usr/share/file/magic.mgc',
    file: '/usr/share/backgrounds/vienna-5164602.jpg',
    mode: LibmagicRb::NONE
)

cookie.check()    # => "JPEG image data, JFIF standard 1.01, resolution (DPI), density 300x300, segment length 16, Exif Standard: [TIFF image data, big-endian, direntries=4, manufacturer=NIKON CORPORATION, model=NIKON D5300], baseline, precision 8, 5959x3973, components 3""
cookie.close()    # => #<LibmagicRb:0x000055fa77699818 @closed=true, @db="/home/sourav/.gem/ruby/3.0.0/gems/libmagic_rb-0.1.0/data/magic.mgc", @file="/usr/share/backgrounds/vienna-5164602.jpg", @mode=1106>
cookie.closed?() # => true
```
Surely, you can automatically get db path if you pass nil to it.  But If you happen to remove the database file or you are unsure, `db: nil` will not work (so will linux's file command).
Specifying the path gives you the privilege to pass a locally stored database.

Do note that there should be version match for the magic files, otherwise it will raise `LibmagicRb::InvalidDBError`.

### Example 3:
LibmagicRb also provides a handy singleton method `:check`. You just need to pass the filename and modes:

```
require 'libmagic_rb'

LibmagicRb.check(file: '/dev/zero', mode: LibmagicRb::MAGIC_NONE)    #=> "character special (1/5)"
LibmagicRb.check(file: '/', mode: LibmagicRb::MAGIC_NONE)    # => "directory"
LibmagicRb.check(file: '/')    # => "inode/directory; charset=binary"
```

Optional:
+ You can use the db: keyword for a custom path. By default it's set to nil. And as mentioned above, nil = automatically find the db from the system.
+ The `mode:` key is optional, by default it's set to `LibmagicRb::MAGIC_MIME | LibmagicRb::MAGIC_CHECK | LibmagicRb::MAGIC_SYMLINK`.

Notes:
+ It's really **mandatory** to close the cookie (`cookie.close()`) when you are done with the cookie. Otherwise, you rely on the GC and that can cause various problems.
  You can't also use the file after it's closed.
+ You can change the file and db on the fly. But you can't change the mode. The mode can be assigned only with LibmagicRb.new(db: ..., file: ..., mode: ...)
+ To list all the modes, please refer to the [man page](https://man7.org/linux/man-pages/man3/magic_getflags.3.html).

### Open Modes
Files can be opened in various modes. You can use this short hand to see the supported modes:

```
LibmagicRb.lsmodes    # => {:MAGIC_NONE=>0, :MAGIC_DEBUG=>1, :MAGIC_SYMLINK=>2, :MAGIC_COMPRESS=>4, :MAGIC_DEVICES=>8, :MAGIC_MIME_TYPE=>16, :MAGIC_MIME_ENCODING=>1024, :MAGIC_MIME=>1040, :MAGIC_CONTINUE=>32, :MAGIC_CHECK=>64, :MAGIC_PRESERVE_ATIME=>128, :MAGIC_RAW=>256, :MAGIC_ERROR=>512, :MAGIC_APPLE=>2048, :MAGIC_EXTENSION=>16777216, :MAGIC_COMPRESS_TRANSP=>33554432, :MAGIC_NO_CHECK_APPTYPE=>32768, :MAGIC_NO_CHECK_CDF=>262144, :MAGIC_NO_CHECK_COMPRESS=>4096, :MAGIC_NO_CHECK_ELF=>65536, :MAGIC_NO_CHECK_ENCODING=>2097152, :MAGIC_NO_CHECK_SOFT=>16384, :MAGIC_NO_CHECK_TAR=>8192, :MAGIC_NO_CHECK_TEXT=>131072, :MAGIC_NO_CHECK_TOKENS=>1048576, :MAGIC_NO_CHECK_CSV=>524288, :MAGIC_NO_CHECK_JSON=>4194304}
```

Note:
+ Some keys can be missing or can have modified values, depending on your libmagic version.

### Parameters

#### Listing parameters

```
LibmagicRb.lsparams    # => {:MAGIC_PARAM_INDIR_MAX=>0, :MAGIC_PARAM_NAME_MAX=>1, :MAGIC_PARAM_ELF_NOTES_MAX=>4, :MAGIC_PARAM_ELF_PHNUM_MAX=>2, :MAGIC_PARAM_ELF_SHNUM_MAX=>3, :MAGIC_PARAM_REGEX_MAX=>5, :MAGIC_PARAM_BYTES_MAX=>6}
```

Note:
+ Some keys can be missing or can have modified values, depending on your libmagic version.

#### Getting parameters

```
cookie.getparam(LibmagicRb::MAGIC_PARAM_REGEX_MAX) # => 8192; but can differ. Returns nil on error.
```

#### Setting parameters
```
cookie.setparam(LibmagicRb::MAGIC_PARAM_REGEX_MAX, 2 ** 14) # => 16384; but can differ. Returns nil on error.
```

#### Notes:

+ To get the parameters, you can run `LibmagicRb.lsparams()` for description, please refer to the [man page](https://man7.org/linux/man-pages/man3/magic_getflags.3.html).
+ `cookie.setparam()` returns the value after getting the param as well. So you don't need to confirm by calling getparam() again.
+ The maximum size depends on the parameter. But the value that can be passed should not be more than 2 ** 32.
+ On older versions of libmagic, where the function isn't available, both getparam() and setparam() will perform no operations, and return nil!

## Errors
The following errors are implemented and raised on appropriate situation:

1. `LibmagicRb::FileNotFound`: When the file is not found.
2. `LibmagicRb::FileUnreadable`: When the file is unreadable.
3. `LibmagicRb::InvalidDBError`: When the database given is invalid.
4. `LibmagicRb::IsDirError`: When the database path is a directory.
5. `LibmagicRb::FileClosedError`: When the file is already closed (closed?()) but you are trying to access the cookie.

## Development

To install this gem onto your local machine, run `bundle exec rake install`. To release a new version, update the version number in `version.rb`, and then run `bundle exec rake release`, which will create a git tag for the version.

## Contributing

Bug reports and pull requests are welcome on GitHub at [https://github.com/cybergizer-hq/LibmagicRb](https://github.com/cybergizer-hq/LibmagicRb) This project is intended to be a safe, welcoming space for collaboration.

## License

The gem is available as open-source under the terms of the [MIT License](https://opensource.org/licenses/MIT).
