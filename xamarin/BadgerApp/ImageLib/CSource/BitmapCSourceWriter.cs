using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ImageLib.CSource;
using System.IO;

namespace ImageLib.CSource
{
	public class BitmapCSourceWriter
	{
		private class FileTypeInfo
		{
			public FileFormatDefs.FileType Type;
			public string IncludePath;
			public string ClassName;
			public string ConstructionArgs;
			public byte BitmapByteDepth;
			public byte PaletteByteDepth;
		}

		public BitmapCSourceFile File { get; set; }
		public string OuterNamespace { get; set; }
		public string BitmapName { get; set; }

		public FileFormatDefs.FileType? TargetFileType
		{
			get => !(m_FileTypeInfo is null) ? (Nullable<FileFormatDefs.FileType>)m_FileTypeInfo.Type : null;
			set => m_FileTypeInfo = value.HasValue ? GetFileTypeInfo(value.Value) : null;
		}

		private StreamWriter m_Writer = null;
		private FileTypeInfo m_FileTypeInfo = null;
		private string m_Indent = "";

		private const string PROP_BITMAP_WIDTH = "WIDTH";
		private const string PROP_BITMAP_HEIGHT = "HEIGHT";
		private const string PROP_BITMAP_BYTE_DEPTH = "BYTE_DEPTH";
		private const string PROP_BITMAP_DATA_LENGTH = "DATA_LENGTH";
		private const string PROP_BITMAP_DATA = "DATA";
		private const string PROP_PALETTE_LENGTH = "PALETTE_LENGTH";
		private const string PROP_PALETTE_BYTE_DEPTH = "PALETTE_BYTE_DEPTH";
		private const string PROP_PALETTE_DATA_LENGTH = "PALETTE_DATA_LENGTH";
		private const string PROP_PALETTE_DATA = "PALETTE_DATA";
		private const string PROP_BITMAP_INSTANCE = "BITMAP";

		public void Write(StreamWriter outFile)
		{
			if ( outFile is null )
			{
				throw new ArgumentNullException("outFile was null.");
			}

			if ( File is null )
			{
				throw new ArgumentNullException("Bitmap file was not set.");
			}

			if ( !File.IsValid )
			{
				throw new ArgumentException("Bitmap file was not valid.");
			}

			if ( OuterNamespace.Length < 1 )
			{
				throw new ArgumentException("Outer namespace was not set.");
			}

			if ( BitmapName.Length < 1 )
			{
				throw new ArgumentException("Bitmap name was not set.");
			}

			if ( !TargetFileType.HasValue )
			{
				throw new ArgumentNullException("Target file type was not set.");
			}

			InitialiseForWrite(outFile);
			WriteInternal();
			CleanUpAfterWrite();
		}

		private void WriteInternal()
		{
			WriteWithIndent("#pragma once");
			WriteBlankLine();

			WriteWithIndent("#include <cstddef>");
			WriteWithIndent("#include <cstdint>");
			WriteWithIndent($"#include <{m_FileTypeInfo.IncludePath}>");
			WriteBlankLine();

			WriteWithIndent($"namespace {OuterNamespace}");
			WriteWithIndent("{");

			IncreaseIndent();
			WriteInnerNamespace();
			DecreaseIndent();

			WriteWithIndent("}");
			WriteBlankLine();
		}

		private void WriteInnerNamespace()
		{
			WriteWithIndent($"namespace {BitmapName}");
			WriteWithIndent("{");

			IncreaseIndent();
			WriteInnerNamespaceContents();
			DecreaseIndent();

			WriteWithIndent("}");
		}

		private void WriteInnerNamespaceContents()
		{
			if ( File.HasPalette )
			{
				WriteWithIndent($"static constexpr size_t {PROP_PALETTE_LENGTH} = {File.Palette.Length / m_FileTypeInfo.PaletteByteDepth};");
				WriteWithIndent($"static constexpr size_t {PROP_PALETTE_BYTE_DEPTH} = {m_FileTypeInfo.PaletteByteDepth};");
				WriteWithIndent($"static constexpr size_t {PROP_PALETTE_DATA_LENGTH} = {PROP_PALETTE_LENGTH} * {PROP_PALETTE_BYTE_DEPTH};");
				WriteBlankLine();

				WriteWithIndent($"static constexpr uint8_t {PROP_PALETTE_DATA}[{PROP_PALETTE_DATA_LENGTH}] =");
				WriteWithIndent("{");

				IncreaseIndent();
				WriteDataArrayContents(File.Palette);
				DecreaseIndent();

				WriteWithIndent("};");
				WriteBlankLine();
			}

			WriteWithIndent($"static constexpr size_t {PROP_BITMAP_WIDTH} = {File.Width};");
			WriteWithIndent($"static constexpr size_t {PROP_BITMAP_HEIGHT} = {File.Height};");
			WriteWithIndent($"static constexpr size_t {PROP_BITMAP_BYTE_DEPTH} = {m_FileTypeInfo.BitmapByteDepth};");
			WriteWithIndent($"static constexpr size_t {PROP_BITMAP_DATA_LENGTH} = {PROP_BITMAP_WIDTH} * {PROP_BITMAP_HEIGHT} * {PROP_BITMAP_BYTE_DEPTH};");
			WriteBlankLine();

			WriteWithIndent($"static constexpr uint8_t {PROP_BITMAP_DATA}[{PROP_BITMAP_DATA_LENGTH}] =");
			WriteWithIndent("{");

			IncreaseIndent();
			WriteDataArrayContents(File.Data);
			DecreaseIndent();

			WriteWithIndent("};");
			WriteBlankLine();

			WriteWithIndent($"static constexpr {m_FileTypeInfo.ClassName} {PROP_BITMAP_INSTANCE}({m_FileTypeInfo.ConstructionArgs});");
		}

		private void WriteDataArrayContents(byte[] arr)
		{
			List<string> arrayDataStrings = CSourceUtils.ToHexArrayString(arr);

			foreach ( string line in arrayDataStrings )
			{
				WriteWithIndent(line);
			}
		}

		private void InitialiseForWrite(StreamWriter outFile)
		{
			m_Writer = outFile;
			m_Indent = "";
		}

		private void CleanUpAfterWrite()
		{
			m_Writer = null;
			m_Indent = "";
		}

		private void WriteWithIndent(string line)
		{
			m_Writer.WriteLine(m_Indent + line);
		}

		private void WriteBlankLine()
		{
			m_Writer.WriteLine();
		}

		private void IncreaseIndent()
		{
			m_Indent += "\t";
		}

		private void DecreaseIndent()
		{
			if ( m_Indent.Length > 0 )
			{
				m_Indent = m_Indent.Substring(1);
			}
		}

		private static FileTypeInfo GetFileTypeInfo(FileFormatDefs.FileType type)
		{
			FileTypeInfo info = new FileTypeInfo
			{
				Type = type
			};

			switch ( type )
			{
				case FileFormatDefs.FileType.BitmapMask:
				{
					info.ClassName = "BadgerGL::BitmapMask";
					info.IncludePath = "BadgerGL/BitmapMask.h";
					info.ConstructionArgs = $"{PROP_BITMAP_WIDTH}, {PROP_BITMAP_HEIGHT}, {PROP_BITMAP_DATA}";
					info.BitmapByteDepth = 1;
					info.PaletteByteDepth = 0;
					break;
				}

				case FileFormatDefs.FileType.Bitmap65K:
				{
					info.ClassName = "BadgerGL::ConstBitmapSurface";
					info.IncludePath = "BadgerGL/BitmapSurface.h";
					info.ConstructionArgs = $"{PROP_BITMAP_WIDTH}, {PROP_BITMAP_HEIGHT}, &BadgerGL::PIXELFORMAT_65K, {PROP_BITMAP_DATA}";
					info.BitmapByteDepth = 2;
					info.PaletteByteDepth = 0;
					break;
				}

				case FileFormatDefs.FileType.Bitmap65KPalette:
				{
					info.ClassName = "BadgerGL::ConstBitmapSurface";
					info.IncludePath = "BadgerGL/BitmapSurface.h";
					info.ConstructionArgs = $"{PROP_BITMAP_WIDTH}, {PROP_BITMAP_HEIGHT}, {PROP_BITMAP_DATA}, &BadgerGL::PIXELFORMAT_65K, {PROP_PALETTE_LENGTH}, {PROP_PALETTE_DATA}";
					info.BitmapByteDepth = 1;
					info.PaletteByteDepth = 2;
					break;
				}

				default:
				{
					throw new NotImplementedException("Specified file type is not implemented yet!");
				}
			}

			return info;
		}
	}
}
