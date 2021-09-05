#!/usr/bin/env ruby

module Bullet
	@c = %W(\u2B53 \u2B1F \u2B22 \u2B23 ).each(&:freeze)

	def self.get() @c.rotate![0] end
end

RSpec.describe LibmagicRb do
	it "#{Bullet.get} has a version number" do
		expect(LibmagicRb::VERSION).not_to be nil
	end

	it "#{Bullet.get} has a String magic version number" do
		expect(LibmagicRb::MAGIC_VERSION).to be_a String
	end

	it "#{Bullet.get} has a check method which returns inode/directory on pwd" do
		expect(LibmagicRb.check(file: Dir.pwd)).to be == "inode/directory; charset=binary"
	end

	it "#{Bullet.get} returns __FILE__ as text/x-ruby; charset=us-ascii" do
		expect(LibmagicRb.check(file: __FILE__)).to be == "text/x-ruby; charset=us-ascii"
	end

	it "#{Bullet.get} can create and close multiple cookies with the LibmagicRb#new" do
		a = LibmagicRb.new(file: Dir.pwd)
		b = LibmagicRb.new(file: __FILE__)

		expect(a.check).to be == "inode/directory; charset=binary"
		expect(b.check).to be == "text/x-ruby; charset=us-ascii"

		a.close
		expect(a.closed?).to be true
		expect(b.closed?).to be false

		b.close
		expect(b.closed?).to be true
	end

	# File change through attribute accessor
	it "#{Bullet.get} can change filename on  the fly" do
		cookie = LibmagicRb.new(file: "invalidFileName-#{Time.now.to_f}.mp3")
		cookie.file = '.'
		expect(cookie.check).to be == "inode/directory; charset=binary"
		cookie.close
	end

	it "#{Bullet.get} can change database file on  the fly" do
		cookie = LibmagicRb.new(file: ?., db: "invalidFileName-#{Time.now.to_f}.mgc")
		cookie.db = nil
		expect(cookie.check).to be == "inode/directory; charset=binary"
		cookie.close
	end

	# Flags / Modes
	it "#{Bullet.get} can change modes on  the fly" do
		cookie = LibmagicRb.new(file: ?.)
		expect(cookie.check).to be == "inode/directory; charset=binary"

		cookie.mode = LibmagicRb::MAGIC_RAW
		expect(cookie.check).to be == "directory"

		cookie.file = __FILE__
		cookie.mode = LibmagicRb::MAGIC_RAW
		expect(cookie.check).to be == "Ruby script, ASCII text"

		cookie.file = Dir.pwd
		cookie.mode = LibmagicRb::MAGIC_MIME_ENCODING
		expect(cookie.check).to be == "binary"

		cookie.close
	end

	# Errors
	it "#{Bullet.get} raises error on invalid filename" do
		cookie = LibmagicRb.new(file: "invalidFileName-#{Time.now.to_f}.mp3")
		expect { cookie.check }.to raise_error LibmagicRb::FileNotFound
		cookie.close
	end
end
