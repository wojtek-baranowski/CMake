CMAKE_VS_PLATFORM_TOOLSET_HOST_ARCHITECTURE
-------------------------------------------

Visual Studio preferred tool architecture (``x64`` or empty).

The :ref:`Visual Studio Generators` for VS 2013 and above support optional
selection of a 64-bit toolchain on 64-bit hosts by specifying a ``host=64``
value in the :variable:`CMAKE_GENERATOR_TOOLSET` option.  The value of this
variable indicates the selected toolchain architecture preference.  Note
that this is only a preference specified in the generated project files.
MSBuild may still choose a different tool architecture, such as when on
a 32-bit host.
