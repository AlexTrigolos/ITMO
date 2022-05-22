import { ApiProperty } from '@nestjs/swagger';
import { ValidateIf } from 'class-validator';

export class AddPostUserDto {
  @ApiProperty()
  @ValidateIf((object, value) => value !== undefined)
  readonly email: string;

  @ApiProperty()
  @ValidateIf((object, value) => value !== undefined)
  readonly postId: number;
}
