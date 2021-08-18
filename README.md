# LibmagicRb
Adds ability to check mime-type of a file using the libmagic ([magic(4)](https://man7.org/linux/man-pages/man4/magic.4.html)).
It uses native extensions and it's quite performant.

## Pre-Installation
On Linux, you need to install libmagic.

##### Arch:

```
# pacman -S file gcc make
```

#### Debian / Ubuntu / Linux Mint / Kali / ParrotOS / RaspberryPi OS:

```
# apt install libmagic-dev ruby-dev gcc make
```

#### Fedora:

```
# yum install file-devel ruby-devel gcc make
```

Mac is currently not supported but may support in the future.

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

## Usage
The target of this gem is to add mime-type checking easily.

Using the LibmagicRb class we can check the mime type, EXIF data and other information of a file.
This gem packs the compiled magic database as well.

To check a file, you need to pass a hash argument to the FilemagicRb.new():

1. db: Path to the Database (String) (To use the internal database packed by this app, use LibmagicRb::DB)
2. file: A file to check (String)
3. mode: Modes of the file (Integer) (Optional, defaults to `LibmagicRb::MAGIC_MIME | LibmagicRb::MAGIC_CHECK | LibmagicRb::MAGIC_SYMLINK`)

### Example 1:

```
require 'libmagic_rb'

cookie = LibmagicRb.new(
    db: LibmagicRb::DB,
    file: '/usr/share/backgrounds/myimage.webp',
    mode: LibmagicRb::MAGIC_MIME | LibmagicRb::MAGIC_CHECK | LibmagicRb::MAGIC_SYMLINK
)

p cookie # =>    #<LibmagicRb:0x000055cf96d8f868 @db="/home/sourav/.gem/ruby/3.0.0/gems/libmagic_rb-0.1.0/data/magic.mgc", @file="/usr/share/backgrounds/myimage.webp", @mode=1106, @closed=false>

# In case The file path needs to be changed
cookie.file = '/usr/share/backgrounds/vienna-5164602.jpg'

p cookie.file    # => "/usr/share/backgrounds/vienna-5164602.jpg"
p cookie.db    # => "/home/cybergizer/.gem/ruby/3.0.0/gems/libmagic_rb-0.1.0/data/magic.mgc"

cookie.check()    # => image/jpeg; charset=binary
cookie.close()    # => #<LibmagicRb:0x000055fa77699818 @closed=true, @db="/home/sourav/.gem/ruby/3.0.0/gems/libmagic_rb-0.1.0/data/magic.mgc", @file="/usr/share/backgrounds/vienna-5164602.jpg", @mode=1106>
cookie.closed?() # => true
```

### Example 2:
```
require 'libmagic_rb'

cookie = LibmagicRb.new(
    db: LibmagicRb::DB,
    file: '/usr/share/backgrounds/vienna-5164602.jpg',
    mode: LibmagicRb::NONE
)

cookie.check()    # => "JPEG image data, JFIF standard 1.01, resolution (DPI), density 300x300, segment length 16, Exif Standard: [TIFF image data, big-endian, direntries=4, manufacturer=NIKON CORPORATION, model=NIKON D5300], baseline, precision 8, 5959x3973, components 3""
cookie.close()    # => #<LibmagicRb:0x000055fa77699818 @closed=true, @db="/home/sourav/.gem/ruby/3.0.0/gems/libmagic_rb-0.1.0/data/magic.mgc", @file="/usr/share/backgrounds/vienna-5164602.jpg", @mode=1106>
cookie.closed?() # => true
```

### Example 3:
LibmagicRb also provides a handy singleton method `:check`. You just need to pass the filename and modes:

```
require 'libmagic_rb'

LibmagicRb.check(file: '/dev/zero', mode: LibmagicRb::MAGIC_NONE)    #=> "character special (1/5)"
LibmagicRb.check(file: '/', mode: LibmagicRb::MAGIC_NONE)    # => "directory"
LibmagicRb.check(file: '/')    # => "inode/directory; charset=binary"
```

Optional:
+ You can use the db: keyword for a custom path. By default it's set to LibmagicRb::DB.
+ The mode is optional, by default it's `LibmagicRb::MAGIC_MIME | LibmagicRb::MAGIC_CHECK | LibmagicRb::MAGIC_SYMLINK`.

Notes:
+ It's really **mandatory** to close the cookie (`cookie.close()`) when you are done with the cookie. Otherwise, you rely on the GC and that can cause various problems.
  You can't also use the file after it's closed.
+ You can change the file and db on the fly. But you can't change the mode. The mode can be assigned only with LibmagicRb.new(db: ..., file: ..., mode: ...)
+ To list all the modes, please refer to the [man page](https://man7.org/linux/man-pages/man3/magic_getflags.3.html).

### Parameters

#### Getting parameters

```
cookie.getparam(LibmagicRb::MAGIC_PARAM_REGEX_MAX) # => 8192; but can differ. Returns nil on error.
```

#### Setting parameters
```
cookie.setparam(LibmagicRb::MAGIC_PARAM_REGEX_MAX, 2 ** 14) # => 16384; but can differ. Returns nil on error.
```

#### Notes:

+ To get the parameters, you can refer to the [man page](https://man7.org/linux/man-pages/man3/magic_getflags.3.html).
+ Cookie setparam returns the value after getting the param as well. So you don't need to confirm by calling getparam() again.
+ The maximum size depends on the parameter. But the value that can be passed should not be more than 2 ** 32.

## Errors
The following errors are implemented and raised on appropriate situation:

1. LibmagicRb::FileNotFound: When the file is not found.
2. LibmagicRb::FileUnreadable: When the file is unreadable.
3. LibmagicRb::InvalidDBError: When the database given is invalid.
4. LibmagicRb::IsDirError: When the database path is a directory.
5. LibmagicRb::FileClosedError: When the file is already closed (closed?()) but you are trying to access the cookie.

## Development

To install this gem onto your local machine, run `bundle exec rake install`. To release a new version, update the version number in `version.rb`, and then run `bundle exec rake release`, which will create a git tag for the version.

## Contributing

Bug reports and pull requests are welcome on GitHub at [https://github.com/cybergizer-hq/LibmagicRb](https://github.com/cybergizer-hq/LibmagicRb) This project is intended to be a safe, welcoming space for collaboration.

## License

The gem is available as open-source under the terms of the [MIT License](https://opensource.org/licenses/MIT).
